# Device Tree Parser Tool

A lightweight C-based tool for parsing and inspecting **Device Tree Blobs (DTB)** using the [libfdt] library.  
This project is designed for developers working on **BSPs, embedded Linux, U-Boot, or OpenWRT**, as well as anyone who wants to **learn how Device Trees work at a low level**.

# Get Start

Follow the steps below to build and run the Device Tree Parser Tool.

### 1. Prerequisites
Before building, make sure your system has:
- A C compiler (`gcc`)
- `make`
- The [libfdt] library: git clone git://git.kernel.org/pub/scm/utils/dtc/dtc.git

### 2. Clone the repository

- git clone https://github.com/your-username/device-tree-parser.git
- cd device-tree-parser

### 3. Build the project

Simply run:

make all

This will compile parse_device_tree.c and link against libfdt, producing an executable called app.

### 4. Run the tool

Provide a compiled DTB file then configure it in DTB_PATH at makefile

make run

### 5. Output example

The tool will display the properties and subnodes of the target node defined in the code (APP_PARSED_NODE). You can adjust this macro in parse_device_tree.c to parse different nodes.

/memory:
device_type = memory
reg = 0x0 0x40000000
bank-width = 0x8

cpu@0:
compatible = arm,cortex-a15
reg = 0x0

## ✨ Features

- Load and validate a **DTB file**.  
- Parse **string, numeric, and boolean properties**.  
- Handle **multi-string properties** (e.g., `compatible`, `clock-output-names`).  
- Traverse and parse **subnodes**.
- Easy to extend and customize for debugging or exploration.

## 📂 Project Structure
```
device-tree-parser/
├── out/                # Build output directory (compiled binaries, object files)
├── .gitignore          # Git ignore configuration
├── makefile            # Build system configuration
├── parse_device_tree.c # Main source code for the parser tool
└── readme.md           # Project documentation
```

## 🎯 Use Cases

- BSP development: Inspect DTB used in U-Boot or Linux kernel boot.
- Learning: Understand how nodes and properties are structured in binary DTB format.
- Debugging: Quickly check what hardware configurations are described in a DTB file.





