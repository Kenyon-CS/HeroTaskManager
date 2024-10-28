#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;

// Define the Task structure
struct Task {
    int id;
    int priority;
    int duration; // in seconds

    // Constructor
    Task(int i, int p, int d) : id(i), priority(p), duration(d) {}
};

// Comparator for priority queue (higher priority first)
struct CompareTask {
    bool operator()(const Task& t1, const Task& t2) {
        // Higher priority first; if equal, shorter duration first
        return t1.priority < t2.priority || 
               (t1.priority == t2.priority && t1.duration > t2.duration);
    }
};

// Function to display the priority queue
void displayQueue(priority_queue<Task, vector<Task>, CompareTask> pq) {
    while (!pq.empty()) {
        Task t = pq.top();
        cout << "[ID:" << t.id << " P:" << t.priority << " D:" << t.duration << "] ";
        pq.pop();
    }
    cout << endl;
}

// Main simulation function
void heroTaskManagerSimulation(int maxTasks) {
    priority_queue<Task, vector<Task>, CompareTask> taskQueue;
    int taskId = 1;

    cout << left << setw(20) << "Incoming Tasks" << setw(25) << "Completed Tasks" << "Current Queue" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < maxTasks; ++i) {
        // Randomly generate new task parameters
        int priority = rand() % 5 + 1; // Priority from 1 to 5
        int duration = rand() % 5 + 1; // Duration from 1 to 5 seconds
        Task newTask(taskId++, priority, duration);

        // Add the new task to the queue
        taskQueue.push(newTask);

        // Display incoming task
        cout << left << setw(20) << "[ID:" + to_string(newTask.id) + " P:" + to_string(newTask.priority) +
                                    " D:" + to_string(newTask.duration) + "]";

        // Process the top task if queue is not empty
        if (!taskQueue.empty()) {
            Task topTask = taskQueue.top();
            taskQueue.pop();

            // Simulate task processing (sleep to represent task duration)
            this_thread::sleep_for(chrono::seconds(topTask.duration));

            // Display completed task
            cout << setw(25) << "[ID:" + to_string(topTask.id) + " P:" + to_string(topTask.priority) +
                                      " D:" + to_string(topTask.duration) + "]";

            // Display current contents of priority queue
            displayQueue(taskQueue);
        } else {
            cout << setw(25) << "No task completed.";
            cout << "Empty queue." << endl;
        }

        // Delay between task arrivals
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    int maxTasks = 10; // Number of tasks for the simulation
    heroTaskManagerSimulation(maxTasks);

    return 0;
}
