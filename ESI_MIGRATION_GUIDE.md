# ESI Migration Guide: Full RIOP → DI/DO Only

## What Changed

The ICC-generated files in `glue/` were regenerated with a simplified object dictionary — just 2 digital inputs (0x6000) and 2 digital outputs (0x7000), all UNSIGNED8. The RIOP reference in `RIOP-ECAT-APP-GLUE-V1.5.0/` had 32 DI + 32 DO + LED + 16 ADC channels across 4 objects (0x6010, 0x6020, 0x7000, 0x7010).

---

## Issues Found in `glue/` (ICC-Generated Files)

Comparing `glue/` against the working `RIOP-ECAT-APP-GLUE-V1.5.0/`, there are several problems that will prevent the new files from working as-is. They are listed below in priority order.

### CRITICAL: SM2/SM3 Disabled in `ecat_conf.h`

**File:** `glue/ecat_conf.h` lines 121, 130

```c
#define EC_CONFIG_SM_2_ENABLED 0   // <-- MUST be 1 for RxPDO
#define EC_CONFIG_SM_3_ENABLED 0   // <-- MUST be 1 for TxPDO
```

SM2 is the RxPDO sync manager and SM3 is the TxPDO sync manager. With both disabled, **no PDO data will be exchanged at all**. The slave will go to OP state but silently ignore all process data.

**Fix:** Change both to `1`. This is likely an ICC configuration issue — in ICC, make sure the PDO sync managers are enabled before regenerating.

### CRITICAL: PDO Mappings Only Map 1 of 2 Sub-indices

**File:** `glue/goal_appl_ecat_objects.c`

The 0x1600 (RxPDO mapping) has `Number of Entries = 0x01` and only one mapping entry:
- 0x1600:01 = `0x70000108` → maps 0x7000:01 (Output 1), 8 bits

The 0x1A00 (TxPDO mapping) similarly has `Number of Entries = 0x01`:
- 0x1A00:01 = `0x60000108` → maps 0x6000:01 (Input 1), 8 bits

**0x6000:02 (Input 2) and 0x7000:02 (Output 2) exist in the dictionary but are NOT actually PDO-mapped.** The master will only see 1 byte in each direction.

**Fix options:**
- **If you only need 1 input + 1 output:** This is fine. Remove 0x6000:02 and 0x7000:02 or leave them as SDO-only.
- **If you need both mapped:** Add a second mapping entry to each PDO mapping object. In `goal_appl_ecat_objects.c`, for 0x1600:
  - Change `Number of Entries` default from `0x01` to `0x02`
  - Add 0x1600:02 with default value `0x70000208` (maps 0x7000:02, 8 bits)
  - Similarly for 0x1A00, add 0x1A00:02 = `0x60000208`
  - Update `EC_CONFIG_MAX_RPDO_DATA` and `EC_CONFIG_MAX_TPDO_DATA` from 1 to 2

This must also be fixed in ICC and the ESI regenerated to match.

### CRITICAL: No Variable Bindings — PDO Data Inaccessible

**File:** `glue/goal_appl_ecat_objects.c` vs `RIOP-ECAT-APP-GLUE-V1.5.0/goal_appl_ecat_objects.c`

The RIOP reference declares global variables and binds them to each sub-index:
```c
// RIOP reference — has these globals:
uint8_t di1_out;    // bound to 0x6010:0x01 via pointer in goal_ecatdynOdSubIndexAdd()
uint8_t di1_in;     // bound to 0x7000:0x01
// ... 128 variables total
```

The new `glue/` version has **zero global variables** and passes `NULL` as the last argument to every `goal_ecatdynOdSubIndexAdd()` call. This means the GOAL stack manages the memory internally — you have no C variable to read/write in the PDO callbacks.

**Fix:** Add variables and bind them:

In `glue/goal_appl_ecat_objects.c`, add at the top (in the global variables section):
```c
uint8_t di1_in;     /* 0x6000:0x01 Input 1 — TxPDO, slave writes */
uint8_t di2_in;     /* 0x6000:0x02 Input 2 — TxPDO, slave writes */
uint8_t di1_out;    /* 0x7000:0x01 Output 1 — RxPDO, master writes */
uint8_t di2_out;    /* 0x7000:0x02 Output 2 — RxPDO, master writes */
```

In `glue/goal_appl_ecat_objects.h`, add extern declarations:
```c
extern uint8_t di1_in;
extern uint8_t di2_in;
extern uint8_t di1_out;
extern uint8_t di2_out;
```

Then replace the `NULL` in each `goal_ecatdynOdSubIndexAdd()` for 0x6000:01, 0x6000:02, 0x7000:01, 0x7000:02 with the pointer to the corresponding variable:

```c
// 0x6000:0x01 — change last arg from NULL to:
(uint8_t *) &di1_in);

// 0x6000:0x02 — change last arg from NULL to:
(uint8_t *) &di2_in);

// 0x7000:0x01 — change last arg from NULL to:
(uint8_t *) &di1_out);

// 0x7000:0x02 — change last arg from NULL to:
(uint8_t *) &di2_out);
```

### Missing RIOP Integration in `goal_appl.c`

**File:** `glue/goal_appl.c` vs `RIOP-ECAT-APP-GLUE-V1.5.0/goal_appl.c`

| Feature | RIOP reference | glue/ (new) |
|---------|---------------|-------------|
| `#include <goal_dd.h>` | Yes | No |
| `#if RIOP` / `riop_appl_init()` call | Yes | No |
| `goal_ddInit()` / `goal_ddNew()` | Yes (non-RIOP path) | No |
| `goal_ecatCfgBootstrapOn(GOAL_TRUE)` | Yes | No |
| `goal_ecatCfgFoeOn(GOAL_TRUE)` | Yes (non-RIOP path) | No |
| `APPL_ECAT_PDO_BUF_SIZE` | 97 bytes | 1 byte |

**Fixes needed:**
1. Add `#if RIOP` / `riop_appl_init()` in `appl_init()` — this is how the M7 core gets started
2. Add `goal_ecatCfgBootstrapOn(GOAL_TRUE)` in `appl_setup()` — needed for firmware update via FoE
3. Increase `APPL_ECAT_PDO_BUF_SIZE` from 1 to at least 2 (1 byte per mapped sub-index, need enough for both directions). Value of 4 is safe.

### Missing DC Cycle Time Check in `goal_appl_ecat.c`

**File:** `glue/goal_appl_ecat.c` vs `RIOP-ECAT-APP-GLUE-V1.5.0/goal_appl_ecat.c`

| Feature | RIOP reference | glue/ (new) |
|---------|---------------|-------------|
| `#if RIOP` / `#include "gl.h"` | Yes | No |
| `APPL_ECAT_MIN_CYCLE_TIME` | 200000 ns | Not defined |
| `appl_ecatDcSettingsCheck()` | Full implementation | Missing entirely |
| `GOAL_ECAT_CB_ID_NEW_DC_CONFIG` handling | Calls `appl_ecatDcSettingsCheck` | Falls through (no-op) |
| PDO callback bodies | Full RIOP data copy logic | Empty stubs |
| Case fallthrough style | Standard `case:` fallthrough | `GOAL_TARGET_FALLTHROUGH` macro |

**Fixes needed:**
1. Add `appl_ecatDcSettingsCheck()` function with a reasonable min cycle time
2. Wire it to `GOAL_ECAT_CB_ID_NEW_DC_CONFIG` in the callback switch
3. Add `#include "gl.h"` under `#if RIOP`
4. Fill in PDO callbacks (see next section)

### Empty PDO Callbacks

Both `appl_ecatPdoReceived()` and `appl_ecatPdoTxPrepare()` are empty stubs. After adding the variable bindings above, fill them in:

```c
#if RIOP
#include "gl.h"
#define MEMCPY memcpy
#define SIZEOF sizeof
#endif

// ...

static void appl_ecatPdoReceived(GOAL_ECAT_T *pHdlEcat)
{
    UNUSEDARG(pHdlEcat);

#if RIOP
    /* Master wrote Output 1 / Output 2 — push to MCU digital outputs */
    riop_command.mcu_digital_output_command.mcu_digital_output =
        (di1_out & 0x01) | ((di2_out & 0x01) << 1);
#endif
}

static void appl_ecatPdoTxPrepare(GOAL_ECAT_T *pHdlEcat)
{
    UNUSEDARG(pHdlEcat);

#if RIOP
    /* Read MCU digital input pins and send to master */
    di1_in = g_boardStatus.mcu_digital_input_pins_status & 0x01;
    di2_in = (g_boardStatus.mcu_digital_input_pins_status >> 1) & 0x01;
#endif
}
```

---

## Side-by-Side: Object Dictionary Comparison

### RIOP Reference (RIOP-ECAT-APP-GLUE-V1.5.0)

| Object | Type | Sub-indices | Content |
|--------|------|-------------|---------|
| 0x6010 | RECORD (DT6010) | 33 (0x21) | 32 DI readback + LED readback |
| 0x6020 | RECORD (DT6020) | 16 (0x10) | 16 ADC channels (uint32, int32, float) |
| 0x7000 | RECORD (DT7000) | 33 (0x21) | 32 DI control + LED control |
| 0x7010 | RECORD (DT7010) | 16 (0x10) | 16 ADC write-back (unused analog outputs) |
| 0x1600 | RxPDO map | 2 entries | → 0x7000, 0x7010 |
| 0x1A00 | TxPDO map | 2 entries | → 0x6010, 0x6020 |

Total PDO size: 97 bytes per direction (33 + 64 bytes).

### New ICC (glue/)

| Object | Type | Sub-indices | Content |
|--------|------|-------------|---------|
| 0x6000 | ARRAY (UNSIGNED8) | 2 | Input 1, Input 2 |
| 0x7000 | ARRAY (UNSIGNED8) | 2 | Output 1, Output 2 |
| 0x1600 | RxPDO map | 1 entry | → 0x7000:01 only |
| 0x1A00 | TxPDO map | 1 entry | → 0x6000:01 only |

Total PDO size: 1 byte per direction (only 1 sub-index actually mapped).

---

## Full Fix Checklist

### Fixes to ICC-generated files (before copying to build tree)

| # | File | Issue | Fix |
|---|------|-------|-----|
| 1 | `glue/ecat_conf.h` | SM2/SM3 disabled | Set `EC_CONFIG_SM_2_ENABLED 1` and `EC_CONFIG_SM_3_ENABLED 1` |
| 2 | `glue/ecat_conf.h` | PDO data size too small if mapping both | Set `EC_CONFIG_MAX_RPDO_DATA 2` and `EC_CONFIG_MAX_TPDO_DATA 2` |
| 3 | `glue/goal_appl_ecat_objects.c` | No variable bindings (NULL pointers) | Add `uint8_t di1_in/di2_in/di1_out/di2_out` globals and bind them |
| 4 | `glue/goal_appl_ecat_objects.h` | No extern declarations | Add `extern` for the 4 variables |
| 5 | `glue/goal_appl_ecat_objects.c` | 0x1600/0x1A00 only map 1 entry each | Add second mapping entry OR accept only 1 DI + 1 DO |
| 6 | `glue/goal_appl.c` | Missing `riop_appl_init()` | Add `#if RIOP` block in `appl_init()` |
| 7 | `glue/goal_appl.c` | Missing `goal_ecatCfgBootstrapOn()` | Add call in `appl_setup()` |
| 8 | `glue/goal_appl.c` | PDO buffer size = 1 | Increase `APPL_ECAT_PDO_BUF_SIZE` to at least 4 |
| 9 | `glue/goal_appl_ecat.c` | Empty PDO callbacks | Add DI/DO read/write logic under `#if RIOP` |
| 10 | `glue/goal_appl_ecat.c` | Missing DC settings check | Add `appl_ecatDcSettingsCheck()` and wire to callback |
| 11 | `glue/goal_appl_ecat.c` | Missing `#include "gl.h"` | Add under `#if RIOP` |

### Firmware files to simplify (optional — only if removing AFE/siggen)

| # | File | Action |
|---|------|--------|
| 12 | `M7FOLLOWER/source/api_riop.h` | Gut structs to just `mcu_digital_output_command_t` and simple status |
| 13 | `M7FOLLOWER/source/digital_io.c` | Remove AFE/siggen init and FSM in `appl_loop()` |
| 14 | `M7FOLLOWER/source/icc_task/icc_task.c` | Remove AFE/siggen queue dispatch |

### Deployment

| # | Action |
|---|--------|
| 15 | Re-import `glue/ICCTest_ESI.xml` into TwinCAT |
| 16 | Reprogram EEPROM if Vendor ID (0x0000E778) differs from what's on the ESC |

---

## Recommended: Fix in ICC First

Most of the critical issues (SM2/SM3 disabled, incomplete PDO mapping, missing variable bindings) are **ICC configuration problems**. The cleanest path:

1. Open `glue/ICCTest.iccproj` in ICC
2. Enable SM2 and SM3 for PDO exchange
3. Verify both sub-indices are mapped in 0x1600 and 0x1A00
4. Enable "Generate managed variable bindings" (or equivalent) so ICC produces the `extern` variables
5. Regenerate all files
6. Then apply only the RIOP-specific patches (items 6, 7, 9, 10, 11 from the checklist) which ICC can't know about
