# HeroTaskManager
A C++ implementation of a Hero Task Manager game planner

## Hero Task Manager in a Fantasy RPG
Consider a game where you control a hero who needs to complete various tasks in a busy, monster-filled world. Each task type has a priority depending on its urgency, importance, or difficulty. Here’s how a priority queue would help organize these tasks:
1. **Tasks with Different Priorities**: Tasks can vary in urgency:
  - **Fight Monster** (high priority): Monsters are actively attacking, so they need immediate attention.
  - **Heal Wound** (medium priority): After fighting, the hero may need to heal; it’s important but can wait if an immediate threat exists.
  - **Collect Resources** (low priority): Gathering resources for crafting or quests is useful but can be postponed if something more urgent arises.
2. **Scheduling with a Priority Queue**: The game’s task manager adds tasks to a priority queue:
  - Each task type has a priority level (higher priority tasks are at the front of the queue).
  - As the hero completes tasks, the manager pulls the highest-priority task from the queue, ensuring the hero focuses on the most urgent or important task first.
3. **Dynamic Task Management**: During gameplay, new tasks can be added based on in-game events, like a new monster appearing. The priority queue instantly reorders these tasks based on priority, keeping the hero focused on what matters most.
