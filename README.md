---

# CHESS-SIM Setup Guide

This repository contains the implementation of a simulated subsystem for a satellite using NASA’s F´ (F Prime) flight software framework. The objective is to build a component (`CsvTM`) that reads telemetric data from a CSV file and integrates it into an executable deployment (`DeploymentSim`) that can interact with the F´ GDS (Ground Data System). This guide explains how to reproduce the environment, generate the necessary components, configure the project in CLion, and launch the GDS interface.

---

## 1. Ensure Correct Environment

These commands update your Ubuntu/WSL system, install essential build tools, set up Python, and ensure CMake and Git are available. This is required because F´ relies on a Python virtual environment and a CMake/Ninja-based build system.

```bash
sudo apt update
sudo apt upgrade -y
sudo apt install -y git cmake python3 python3-pip python3-venv build-essential
```

---

## 2. Create the Project Directory

This creates a workspace that will hold your F´ project. F´ recommends a clean directory structure where each project lives inside its own folder.

```bash
mkdir fprime-workspace
cd fprime-workspace
```

---

## 3. Create the F´ Project and Activate Its Environment

Here you install the `fprime-bootstrap` tool, generate a new F´ project, and activate the Python virtual environment belonging to it. The environment isolates dependencies and is mandatory for all subsequent F´ commands.

```bash
pip install fprime-bootstrap
fprime-bootstrap project CHESS-SIM "ChessSim"
cd CHESS-SIM
source fprime-venv/bin/activate
fprime-util generate
```

---

## 4. Create the New Component

This step generates the skeleton for a new F´ component inside the `ChessSim` namespace. You will later implement its logic by editing the `.hpp`, `.cpp`, and `.fpp` files generated here.

```bash
cd ChessSim/Components
fprime-util new --component
```

**Inputs:**

* Name: `CsvTM`
* Description: `Reads CSV Simulation Data`
* Default values for the rest.

---

## 5. Open CLion and Configure the Project

CLion must be configured properly so it can:

* use the correct CMake binary inside the F´ virtual environment,
* build inside the designated F´ build folder,
* run with the WSL toolchain.

### **Toolchains**

Navigate to:
`File → Settings → Build, Execution, Deployment → Toolchains`

Configure:

* **Toolset:** Ubuntu-22.04
* **CMake:**
  `\\wsl.localhost\Ubuntu-22.04\home\pablo\CHESS-MCS\fprime-workspace\CHESS-SIM\fprime-venv\bin\cmake`
  (This ensures CLion uses the F´ environment's CMake.)
* **Debugger:** WSL GDB

### **CMake**

Navigate to:
`File → Settings → Build, Execution, Deployment → CMake`

Set:

* **Toolchain:** Ubuntu-WSL (default)
* **Generator:** Ninja
* **Build directory:**
  `\\wsl.localhost\Ubuntu-22.04\home\pablo\CHESS-MCS\fprime-workspace\CHESS-SIM\build-fprime-automatic-native`

Afterwards, reload the CMake project:

**File → “Reload CMake Project”**

Repeat until no errors remain. Expected final output:

```
Build files have been written to: /home/pablo/CHESS-MCS/fprime-workspace/CHESS-SIM/build-fprime-automatic-native
[Finished]
```

---

## 6. Create Sample Simulation Data

This creates a simple CSV-like file containing floating-point values sampled every second. The `CsvTM` component will read these values and publish them as telemetry.

```bash
echo -e "0.9\n20.5\n40.1\n60.8\n80.9\n100.0" > sim_data.csv
```

---

## 7. Implement the CsvTM Component

These are the files you need to edit to define the component’s behavior:

* `CsvTM.hpp` — Component class definition
* `CsvTM.cpp` — Implementation logic
* `CsvTM.fpp` — F´ interface definition

They are located in:

```
fprime-workspace/CHESS-SIM/ChessSim/Components/CsvTM
```

After editing, rebuild the project to propagate and generate the updated sources:

```bash
fprime-util purge
fprime-util generate
fprime-util build
```

---

## 8. Create the Deployment (FS Executable)

A deployment defines the topology (components, wiring, and ports) of the system. This step generates a new deployment folder and initial FPP files.

```bash
cd CHESS-SIM/
fprime-util new --deployment
```

**Inputs:**

* Name: `DeploymentSim`
* Defaults for the rest.

### Edit deployment files under:

```
fprime-workspace/CHESS-SIM/DeploymentSim/Top
```

Files to modify:

* `topology.fpp` — System architecture
* `instances.fpp` — Component instantiation and connections

Check formatting and dependencies:

```bash
fprime-util fpp-check    # A small ERROR with 'fpp-import-list' is expected
fprime-util build
```

---

## 9. Launch the F´ GDS GUI

The GDS lets you view telemetry and send commands to your deployment. Run:

```bash
fprime-gds
```

Then open in your browser:

```
http://127.0.0.1:5000/
```

---