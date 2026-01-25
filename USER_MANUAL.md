# Ride-Sharing Dispatch System - User Manual

## 1. System Overview
This project is a high-performance, in-memory ride-sharing dispatch system designed to simulate real-world scenarios. It efficiently matches riders with the nearest available drivers using graph algorithms and manages trip lifecycles with a robust state machine that supports rollbacks.

## 2. Architecture
The system follows a modular 3-tier architecture:

- **Frontend (UI)**: Built with **HTML5, TailwindCSS**, and **JavaScript**. It provides a modern, glassmorphism-styled interface for users to book rides and visualize driver assignments.
- **Middleware (API)**: A lightweight **Java HTTP Server**. It acts as a bridge, serving the frontend and invoking the C++ core for logic processing.
- **Backend (Core)**: Written in **C++**. It handles the heavy lifting: graph management, Dijkstra's shortest path algorithm, driver matching, and transaction rollbacks.

## 3. Prerequisites
Ensure you have the following installed on your Linux system:
- **C++ Compiler**: `g++` (supports C++11 or later)
- **Java Development Kit (JDK)**: `javac` and `java` runtimes.
- **Shell**: Bash (standard on Linux/macOS).

## 4. Installation & Building
We have provided an automated script to build and run the entire system in one step.

1. **Unzip/Clone** the project repository.
2. **Open a terminal** in the project root directory.
3. **Run the startup script**:
   ```bash
   ./run.sh
   ```
   *This script automates the compiling of the C++ backend, the Java server, and starts the application.*

## 5. Usage Guide

### A. Using the Web Interface (Recommended)
1. After running `./run.sh`, leave the terminal open.
2. Open your web browser (Chrome, Firefox, etc.).
3. Navigate to: [http://localhost:8080](http://localhost:8080)
4. **Request a Ride**:
   - Select your **Pickup Location** from the dropdown.
   - Click **"Find Nearest Driver"**.
   - The system will calculate the optimal driver based on graph distance and display the result.

### B. Running the C++ Test Suite
If you want to verify the internal logic (algorithms, state machine, rollbacks) without the UI:

1. Navigate to the backend directory:
   ```bash
   cd backend
   ```
2. Run the executable directly:
   ```bash
   ./dispatch_system
   ```
   *(This triggers the built-in test suite which runs 10 comprehensive verification tests.)*

### C. CLI "Solve" Mode
You can also run the backend in "Solver" mode manually (this is what the Java server uses):
```bash
./dispatch_system solve <PickupLocation> "Driver1" "Location1" "Driver2" "Location2" ...
```

## 6. Project Structure
```
/root
├── inputs/            # (Optional) Input files
├── backend/           # Core Logic
│   ├── main.cpp       # Entry point & Test Suite
│   ├── City.cpp       # Graph & Dijkstra Algo
│   ├── Driver.cpp     # Driver Entity
│   ├── RideShareServer.java # API Gateway
│   └── ...
├── frontend/          # User Interface
│   └── index.html     # Web App
└── run.sh             # Build & Run Automation
```

## 7. Troubleshooting
- **Port 8080 already in use**:
  - Edit `backend/RideShareServer.java` and change `int port = 8080;` to another number (e.g., 8081).
  - Re-run `./run.sh`.
- **"Permission denied"**:
  - Run `chmod +x run.sh` to make the script executable.

## 8. Credits
**Course**: Advanced Data Structures & Algorithms
**Project**: Ride-Sharing Dispatch & Trip Management
**Team**: 2-Student Group Project
