# Politropy

Computes polytropic models of stars by solving the Lane-Emden equation.

## Compilation

```bash
make
```

The default compiler is `gcc`. To change it, edit the `CC` variable in the Makefile. If library errors occur, install the missing libraries.

## Usage

```
./politropy [option value] ...
```

All options are optional; defaults are used if omitted. Each option must be followed by its value.

| Option | Default | Description |
|--------|---------|-------------|
| `-i, --index` | `3.5` | Polytropic index. Physical solutions exist for `0 < index < 5`; outside this range models are unphysical or the program will not converge. |
| `-s, --const` | `4.5339e14` | Constant K in the polytropic equation. Should be chosen so the model agrees with observations. |
| `-k, --step` | `0.001` | Integration step size. Smaller = more accurate but slower and larger output. |
| `-m, --mass` | `1` | Star mass in solar masses. |
| `-f, --file` | stdout | Output file. **Warning:** existing files will be overwritten. |
| `-z, --output` | `0` | Output mode (see [Output](#output)). |
| `-p, --memory` | `10` | Max memory in MB (approximate). **Warning:** use only with `index >= 5`; for lower indices it may truncate the solution and produce an incorrect model. Prefer reducing step size if memory is limited. |
| `-h, --help` | | Display help. |
| `-v, --version` | | Display version. |

## Output

Controlled by the `-z` / `--output` flag:

| Mode | Columns |
|------|---------|
| `0` | xi, theta, dtheta/dxi, radius, density, pressure, temperature |
| `1` | xi, theta, dtheta/dxi |
| `2` | radius, density, pressure, temperature |

## Integration Methods

Currently available:

- **Adams-Bashforth-Moulton** (predictor-corrector) — the method in use

## Examples

```bash
# Polytropic index 2, mass 3 solar masses, save to file
./politropy -i 2 -m 3 -f result.dat

# Default parameters, limit memory to 1 MB, output Lane-Emden solution only
./politropy -p 1 -z 1
```

## Planned

- Option to limit the number of output rows
- Scripts for building families of solutions (e.g. varying star mass)
- Scripts for automated plot generation
- Improved error handling
- Additional integration methods with runtime selection
