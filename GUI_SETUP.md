# Hospital Management System - GUI Setup Guide

## Overview
A modern graphical user interface (GUI) has been added to your Hospital Management System using the **Qt Framework**. This replaces the console-based interface with a professional window-based application.

## Files Added

### Core GUI Files:
1. **mainwindow.h** - Header file for the main application window
2. **mainwindow.cpp** - Implementation of the GUI interface
3. **main_gui.cpp** - Entry point for the GUI application
4. **Hospital-GUI.pro** - Qt project file for building

## Requirements

Before you can compile and run the GUI, you need to install:

### 1. Qt Framework
- Download from: https://www.qt.io/download
- Choose **Open Source** version
- During installation, select:
  - Qt 6.x (or Qt 5.15)
  - MinGW or MSVC compiler
  - Qt Creator IDE (optional but recommended)

### 2. C++ Build Tools
- MinGW compiler (comes with Qt)
- OR Visual Studio with C++ development tools

## Compilation Instructions

### Option A: Using Qt Creator (Recommended)
1. Open **Qt Creator**
2. Click **File → Open File or Project**
3. Navigate to and open: `Hospital-GUI.pro`
4. Select your compiler (MinGW or MSVC)
5. Click **Configure Project**
6. Press **Ctrl + B** to build
7. Press **Ctrl + R** to run

### Option B: Using Command Line
```bash
cd "c:\Users\lokes\Downloads\Hospital-Management-System-master\Hospital-Management-System-master"

# Run qmake to generate Makefile
qmake Hospital-GUI.pro

# Compile with mingw32-make or nmake
mingw32-make
# or
nmake

# Run the executable
release\HospitalManagementGUI.exe
```

## GUI Features

### Main Menu
- **Admin Panel** - Manage doctors, wards, and hospital operations
- **Patient Menu** - Register and manage patient information
- **Doctor Menu** - View doctor details and schedules
- **Lab Test** - Schedule and view lab test results
- **Ward Admission** - Admit and discharge patients
- **Save/Read Data** - Persist data to files

### Admin Panel Features
- Hire/Manage doctors
- Manage wards and beds
- View doctor and patient information
- Track hospital income

### Patient Menu Features
- Register new patients
- View patient details
- Update patient information

### Doctor Menu Features
- View doctor details
- Manage assigned patients
- Check schedules

## Integration with Existing Code

The GUI is designed to work alongside your existing console application:
- Your original **main.cpp** remains unchanged
- You can run both console and GUI versions
- Data files (Admin.txt) are shared between both interfaces

## File Structure
```
Hospital-Management-System-master/
├── main.cpp (original console application)
├── mainwindow.h (NEW - GUI header)
├── mainwindow.cpp (NEW - GUI implementation)
├── main_gui.cpp (NEW - GUI entry point)
├── Hospital-GUI.pro (NEW - Qt project file)
├── doctor.h (existing)
├── patient.h (existing)
└── Hospital Management System.cbp (existing Code::Blocks project)
```

## Compiling Original Console Version

Your original console application can still be compiled:
```bash
# Using Code::Blocks: Open Hospital Management System.cbp
# Or command line with MinGW: g++ -o HMS main.cpp doctor.h patient.h
```

## Troubleshooting

### Qt not found
- Ensure Qt is properly installed
- Add Qt to PATH environment variable
- Restart Command Prompt/PowerShell after installation

### Compiler errors
- Verify you have a C++11 compatible compiler
- Use the same compiler for both Qt and your application

### Build fails
- Clean the build: Delete `build` folder and `.o` files
- Regenerate with: `qmake Hospital-GUI.pro`

## Next Steps

To further enhance the GUI:
1. Add database connectivity (SQLite, MySQL)
2. Implement data validation
3. Add charts/reports generation
4. Create user login system
5. Add print functionality
6. Implement real-time notifications

## Support & Resources

- Qt Documentation: https://doc.qt.io/
- Qt Tutorial: https://wiki.qt.io/Qt_for_Beginners
- Qt Forum: https://forum.qt.io/
