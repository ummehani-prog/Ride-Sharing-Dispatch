# Ride-Sharing Dispatch & Trip Management System Design

## 1. Graph Representation
The city is modeled as a Weighted Undirected Graph.
- **Nodes**: Locations (Strings). Mapped to integer IDs (indices) for efficient processing.
- **Edges**: Roads between locations with associated weights (Distance).
- **Adjacency Structure**: `vector<Node>` where each `Node` contains a list of `Edge` structs.

### Data Structures
- **Custom Adjacency List**: Implemented using `std::vector` (allowed sequence container) of `Node` structs.
- **Dijkstra's Algorithm**: Used for shortest path calculation.
- **Custom Min-Heap**: (To be implemented) To replace `std::priority_queue` for strict compliance with "No STL graph/map/heap" constraint.

## 2. Trip State Machine
Trips transition through the following states:
1. **REQUESTED**: Initial state when a rider requests a trip.
2. **ASSIGNED**: A driver has been matched and assigned.
3. **ONGOING**: The trip has started (Driver picked up rider).
4. **COMPLETED**: The trip ended successfully.
5. **CANCELLED**: The trip was cancelled before completion.

**Transitions**:
- `REQUESTED` -> `ASSIGNED`
- `ASSIGNED` -> `ONGOING`
- `ONGOING` -> `COMPLETED`
- `REQUESTED` -> `CANCELLED`
- `ASSIGNED` -> `CANCELLED` (Triggers Rollback of driver availability)

## 3. Rollback Strategy
We use a **Command Pattern** approach for rollbacks.
- **Action Record**: Every state-changing operation (Assign, Cancel, Complete) records a reverse `std::function` (lambda) into a stack.
- **Rollback(k)**: pops the last `k` actions from the stack and executes them to restore the previous state.

## 4. Complexity Analysis
- **Space**: O(V + E) for the graph storage.
- **Time**:
  - `shortestPath`: O(E log V) using Binary Heap Dijkstra.
  - `dispatch`: O(D * E log V) in worst case (checking all drivers), but optimized to check available drivers.
  - `rollback`: O(k) where k is the number of steps.

## 5. Analytics
- **Average Trip Distance**: Iterating history of trips.
- **Driver Utilization**: Tracking `completedTrips` per driver.
- **Status Distribution**: Counting trips by state.
