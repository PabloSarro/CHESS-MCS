Here’s your final text formatted as a proper README section, ready to copy-paste:

````markdown
# CHESS-SIM Quick Start Guide

This procedure explains how to run **CHESS-SIM** from a fresh clone.  
Tested on **Ubuntu 22.04** (native Linux and WSL2).  
No prior knowledge of F′ is required and **CLion is optional**.

---

## 1. System prerequisites

Install the minimal dependencies:

```bash
sudo apt update
sudo apt install -y \
  git \
  python3 \
  python3-venv \
  python3-pip \
  cmake \
  build-essential
````

No Conda is required or recommended.

---

## 2. Clone the repository

```bash
git clone https://github.com/PabloSarro/CHESS-MCS.git
cd CHESS-MCS
```

The repository already contains:

* the F′ project,
* the deployment,
* the simulation data,
* and all required configuration files.

No project generation is needed.

---

## 3. Create and activate the Python virtual environment

```bash
python3 -m venv fprime-venv
source fprime-venv/bin/activate
```

All F′ tools and dependencies will live inside this environment.

---

## 4. Install Python dependencies

```bash
pip install -r requirements.txt
```

This installs:

* F′ core tools,
* the F′ GDS,
* and all required Python dependencies.

No additional packages are needed.

---

## 5. Generate and build the project

From the **repository root**:

```bash
fprime-util generate
fprime-util build
```

This step:

* generates F′ sources and dictionaries,
* builds the `DeploymentSim` executable,
* prepares the artifacts required by the GDS.

It only needs to be repeated if the source code changes.

---

## 6. Run the F′ Ground Data System (GDS)

```bash
fprime-gds
```

After a few seconds, the terminal will print:

```
Launched UI at: http://127.0.0.1:5000/
```

Open that address in a browser. You should see:

* the F′ GDS interface,
* telemetry updating once per second from `sim_data.csv`,
* the `DeploymentSim` executable running automatically.

---

## 7. Stopping and restarting

To stop the system:

```text
CTRL-C
```

If you restart immediately and encounter a temporary
`Address already in use` error, wait a few seconds and relaunch:

```bash
fprime-gds
```

This is a known TCP shutdown behavior and not a configuration issue.

---

## 8. Optional: Development with CLion

CLion is **not required** to run the project.
It may be used optionally for development and code editing, but it is **outside the minimal execution path**.

---

## Final notes

* Conda must **not** be used.
* Only the provided `requirements.txt` is needed.
* The project is self-contained.
* The GDS auto-launches the deployment.
* No additional setup steps are required.

```

This can **replace or supplement** your current README to provide a minimal, working guide.
```
