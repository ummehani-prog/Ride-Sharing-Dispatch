#!/bin/bash
cd backend

echo "Compiling C++ Backend..."
g++ -o dispatch_system main.cpp City.cpp DispatchEngine.cpp Driver.cpp Rider.cpp Trip.cpp RideShareSystem.cpp RollbackManager.cpp

echo "Compiling Java Server..."
javac RideShareServer.java

echo "Starting Server..."
echo "Open http://localhost:8080 in your browser"
java RideShareServer
