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
void heroTaskManagerSimulation(int maxTasks, int minTime) {
    priority_queue<Task, vector<Task>, CompareTask> taskQueue;
    int taskId = 1;
    const Task emptyTask(-1,-1,-1);  // This is a flag task.
    Task currentTask = emptyTask;
    
    cout << left << setw(20) << "Incoming Tasks" << setw(25) << "Completed Tasks" << "Current Queue" << endl;
    cout << "------------------------------------------------------------" << endl;

    // Run the simulation for maxTasks Tasks and minTime seconds until everything is done
    int tasks = 0;
    int time = 0;
    while (tasks < maxTasks && minTime > time && !taskQueue.empty()) { 
        string incomingTaskDisplay = "";
        string completedTaskDisplay = "";

        // Each second add a new task with .5 probability if we have more tasks to generate.
        if (rand() % 2 && tasks < maxTasks) {
            // Randomly generate new task parameters
            int priority = rand() % 5 + 1; // Priority from 1 to 5
            int duration = rand() % 5 + 1; // Duration from 1 to 5 seconds
            Task newTask(taskId++, priority, duration);
            tasks++;

            // Add the new task to the queue
            taskQueue.push(newTask);
            tasks++;

            // Format incoming task display
            incomingTaskDisplay = "[ID:" + to_string(newTask.id) + " P:" + to_string(newTask.priority) +
                                  " D:" + to_string(newTask.duration) + "]";
        } else {
            incomingTaskDisplay = "-";
        }

        // Process the current task
        if (currentTask.id != -1) {
            currentTask.duration--;
            if (currentTask.duration <= 0) {
                // Format completed task display
                completedTaskDisplay = "[ID:" + to_string(currentTask.id) + " P:" + to_string(currentTask.priority) +
                                       " D:0]";
                // Start the next task if queue is not empty, otherwise have an empty task
                if (!taskQueue.empty()) {
                    currentTask = taskQueue.top();
                    taskQueue.pop();
                } else {
                    currentTask = emptyTask;
                }
            } else {
                completedTaskDisplay = "-";
            }
        } else if (!taskQueue.empty()) {
            currentTask = taskQueue.top();
            taskQueue.pop();
            completedTaskDisplay = "-";
        } else {
            completedTaskDisplay = "-";
        }

        // Display columns: Incoming Task, Completed Task, and Current Queue
        cout << left << setw(20) << incomingTaskDisplay
             << setw(25) << completedTaskDisplay;
        displayQueue(taskQueue);

        // Simulate one second
        this_thread::sleep_for(chrono::seconds(1));
        time++;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    int maxTasks = 10; // Maximum number of tasks for the simulation
    int minTime = 20;  // Minimum run time for simulation
    heroTaskManagerSimulation(maxTasks, minTime);

    return 0;
}
