#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

// ANSI escape codes for text coloring
const string ANSI_RESET = "\033[0m";
const string ANSI_COLOR_WHITE = "\033[97m";
const string ANSI_COLOR_GREEN = "\033[92m";
const string ANSI_COLOR_RED = "\033[91m";
const string ANSI_COLOR_BLUE = "\033[94m";
const string ANSI_COLOR_LIGHT_WHITE = "\033[97m";
const string ANSI_BOLD = "\033[1m";

struct Task {
    std::string name;
    std::string description;
    int priority;
    Task* next;
    Task* subtasks;
    std::vector<std::string> notes;

    Task(const std::string& name, const std::string& description, int priority)
        : name(name), description(description), priority(priority), next(nullptr), subtasks(nullptr) {}
};

void displayLargeHeader(const string& header, const string& color) {
    cout << color << ANSI_BOLD <<
"888888888888    db         ad88888ba   88      a8P          db         88888888ba,    88888888888\n"
"     88        d88b       d8`     `8b  88    ,88'          d88b        88      ``8b   88\n"
"     88       d8'`8b      Y8,          88  ,88`           d8'`8b       88        `8b  88\n"
"     88      d8'  `8b     `Y8aaaaa,    88,d88'           d8'  `8b      88         88  88aaaaa\n"
"     88     d8YaaaaY8b      ``````8b,  8888`88,         d8YaaaaY8b     88         88  88`````\n"
"     88    d8````````8b           `8b  88P   Y8b       d8````````8b    88         8P  88\n"
"     88   d8'        `8b  Y8a     a8P  88     `88,    d8'        `8b   88      .a8P   88\n"
"     88  d8'          `8b  `Y88888P`   88       Y8b  d8'          `8b  88888888Y`'    88888888888\n"
<< ANSI_RESET << endl;

    int terminalWidth = 80; 
    int padding = (terminalWidth - header.size()) / 2;
    for (int i = 0; i < padding; ++i) {
        cout << " ";
    }
    cout << header << endl;
}
void typewriterAnimation(const string& text, const string& color, int delay = 50) {
    for (char c : text) {
        cout << color << ANSI_BOLD << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
    cout << ANSI_RESET << endl;
}



// Create a singly linked list for tasks
class TaskList {
public:
    Task* head;

    TaskList() : head(nullptr) {}

    void addTask(const std::string& name, const std::string& description, int priority) {
        Task* newTask = new Task(name, description, priority);
        newTask->next = head;
        head = newTask;
        std::cout << "Task '" << name << "' added." << std::endl;
    }

    void deleteTask(const std::string& name) {
        Task* prev = nullptr;
        Task* current = head;

        while (current) {
            if (current->name == name) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                std::cout << "Task '" << name << "' deleted." << std::endl;
                return;
            }
            prev = current;
            current = current->next;
        }
        std::cout << "Task not found." << std::endl;
    }

    void addNoteToTask(Task* task, const std::string& note) {
        task->notes.push_back(note);
        std::cout << "Note added to task '" << task->name << "': " << note << std::endl;
    }

    void displayTasks(Task* node, int depth = 0) {
        while (node) {
            for (int i = 0; i < depth; ++i) {
                cout << "  ";
            }
            cout << ANSI_COLOR_GREEN << "[" << node->name << " (Priority: " << node->priority << ")]" << ANSI_RESET << endl;
            if (!node->description.empty()) {
                for (int i = 0; i < depth + 1; ++i) {
                    cout << "  ";
                }
                cout << "Description: " << node->description << endl;
            }
            for (const auto& note : node->notes) {
                for (int i = 0; i < depth + 1; ++i) {
                    cout << "  ";
                }
                cout << ANSI_COLOR_RED << "Note: " << note << ANSI_RESET << endl;
            }
            if (node->subtasks) {
                for (int i = 0; i < depth + 1; ++i) {
                    cout << "  ";
                }
                cout << ANSI_COLOR_BLUE << "Subtasks:" << ANSI_RESET << endl;
                displayTasks(node->subtasks, depth + 2);
            }
            node = node->next;
        }
    }

    void addSubtask(Task* parent, const std::string& subtaskName, const std::string& subtaskDescription, int subtaskPriority) {
        Task* subtask = new Task(subtaskName, subtaskDescription, subtaskPriority);
        if (!parent->subtasks) {
            parent->subtasks = subtask;
        } else {
            Task* lastSubtask = parent->subtasks;
            while (lastSubtask->next) {
                lastSubtask = lastSubtask->next;
            }
            lastSubtask->next = subtask;
        }
        std::cout << "Subtask '" << subtaskName << "' added to '" << parent->name << "'." << std::endl;
    }

    void setTaskPriority(Task* task, int priority) {
        task->priority = priority;
        std::cout << "Priority of task '" << task->name << "' set to " << priority << "." << std::endl;
    }

    void addTaskDescription(Task* task, const std::string& description) {
        task->description = description;
        std::cout << "Description added to task '" << task->name << "'." << std::endl;
    }

    Task* findTask(Task* node, const std::string& name) {
        if (!node) {
            return nullptr;
        }
        
        if (node->name == name) {
            return node;
        }
        
        Task* subtaskResult = findTask(node->subtasks, name);
        if (subtaskResult) {
            return subtaskResult;
        }
        
        return findTask(node->next, name);
    }

};
int main() {
    TaskList taskList;

    string headline =
        "Welcome to Task Manager";

    displayLargeHeader(headline, ANSI_COLOR_GREEN);
//     typewriterAnimation(
// "888888888888    db         ad88888ba   88      a8P          db         88888888ba,    88888888888\n"
// "     88        d88b       d8`     `8b  88    ,88'          d88b        88      ``8b   88\n"
// "     88       d8'`8b      Y8,          88  ,88`           d8'`8b       88        `8b  88\n"
// "     88      d8'  `8b     `Y8aaaaa,    88,d88'           d8'  `8b      88         88  88aaaaa\n"
// "     88     d8YaaaaY8b      ``````8b,  8888`88,         d8YaaaaY8b     88         88  88`````\n"
// "     88    d8````````8b           `8b  88P   Y8b       d8````````8b    88         8P  88\n"
// "     88   d8'        `8b  Y8a     a8P  88     `88,    d8'        `8b   88      .a8P   88\n"
// "     88  d8'          `8b  `Y88888P`   88       Y8b  d8'          `8b  88888888Y`'    88888888888\n"
// ,ANSI_COLOR_RED,3);
    typewriterAnimation("Initializing Task Manager...",ANSI_COLOR_RED);
    cout << "Type 'help' to see available commands." << endl;

    while (true) {
        string input;
        cout << ANSI_COLOR_LIGHT_WHITE << "> ";
        cin >> input;

        if (input == "help") {
            cout << "Available commands:" << endl;
            cout << "  add: Add a new task" << endl;
            cout << "  addsub: Add a subtask to an existing task" << endl;
            cout << "  setpriority: Set the priority of a task" << endl;
            cout << "  setdescription: Set the description of a task" << endl;
            cout << "  addnote: Add a note to a task" << endl;
            cout << "  delete: Delete a task" << endl;
            cout << "  list: List all tasks" << endl;
            cout << "  quit: Exit the program" << endl;
        } else if (input == "add") {
            string name, description;
            int priority;
            cout << "Enter task name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, description);
            cout << "Enter task priority: ";
            cin >> priority;
            taskList.addTask(name, description, priority);
        } else if (input == "addsub") {
            string parentName, subtaskName, subtaskDescription;
            int subtaskPriority;
            cout << "Enter parent task name: ";
            cin >> parentName;
            cout << "Enter subtask name: ";
            cin >> subtaskName;
            cout << "Enter subtask description: ";
            cin.ignore();
            getline(cin, subtaskDescription);
            cout << "Enter subtask priority: ";
            cin >> subtaskPriority;
            Task* parent = taskList.findTask(taskList.head, parentName);
            if (parent) {
                taskList.addSubtask(parent, subtaskName, subtaskDescription, subtaskPriority);
            } else {
                cout << "Parent task not found." << endl;
            }
        } else if (input == "setpriority") {
            string name;
            int priority;
            cout << "Enter task name: ";
            cin >> name;
            cout << "Enter new priority: ";
            cin >> priority;
            Task* task = taskList.findTask(taskList.head, name);
            if (task) {
                taskList.setTaskPriority(task, priority);
            } else {
                cout << "Task not found." << endl;
            }
        } else if (input == "setdescription") {
            string name, description;
            cout << "Enter task name: ";
            cin >> name;
            cout << "Enter new description: ";
            cin.ignore();
            getline(cin, description);
            Task* task = taskList.findTask(taskList.head, name);
            if (task) {
                taskList.addTaskDescription(task, description);
            } else {
                cout << "Task not found." << endl;
            }
        } else if (input == "addnote") {
            string name, note;
            cout << "Enter task name: ";
            cin >> name;
            cout << "Enter note: ";
            cin.ignore();
            getline(cin, note);
            Task* task = taskList.findTask(taskList.head, name);
            if (task) {
                taskList.addNoteToTask(task, note);
            } else {
                cout << "Task not found." << endl;
            }
        } else if (input == "delete") {
            string name;
            cout << "Enter task name to delete: ";
            cin >> name;
            taskList.deleteTask(name);
        } else if (input == "list") {
            taskList.displayTasks(taskList.head);
        } else if (input == "quit" || input == "exit" || input == "q") {
            break;
        } else {
            cout << "Unknown command." << endl;
            cout << "Available commands:" << endl;
            cout << "  add: Add a new task" << endl;
            cout << "  addsub: Add a subtask to an existing task" << endl;
            cout << "  setpriority: Set the priority of a task" << endl;
            cout << "  setdescription: Set the description of a task" << endl;
            cout << "  addnote: Add a note to a task" << endl;
            cout << "  delete: Delete a task" << endl;
            cout << "  list: List all tasks" << endl;
            cout << "  quit: Exit the program" << endl;

        }
    }

    return 0;
}
