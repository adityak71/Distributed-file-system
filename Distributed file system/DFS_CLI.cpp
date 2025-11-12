#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// ====================== Node Class ======================
class Node {
public:
    string name;
    bool active;
    map<string, string> files; // filename -> content

    Node(string n) {
        name = n;
        active = true;
    }

    void storeFile(const string &filename, const string &data) {
        if (active) {
            files[filename] = data;
            cout  << name << " stored '" << filename << "'" << endl;
        } else {
            cout << name << " is DOWN. Cannot store file.\n";
        }
    }

    bool hasFile(const string &filename) const {
        return files.find(filename) != files.end();
    }

    string getFile(const string &filename) const {
        if (active && hasFile(filename))
            return files.at(filename);
        return "";
    }
};

// ================= Distributed File System =================
class DistributedFileSystem {
private:
    vector<Node*> nodes;
    int replicationFactor;

public:
    DistributedFileSystem(int totalNodes, int replication) {
        replicationFactor = replication;
        for (int i = 0; i < totalNodes; ++i)
            nodes.push_back(new Node("Node_" + to_string(i + 1)));
    }

    void uploadFile(const string &filename, const string &data) {
        cout << "\n Uploading file: " << filename << "...\n";
        int stored = 0;
        for (auto node : nodes) {
            if (node->active) {
                node->storeFile(filename, data);
                stored++;
                if (stored >= replicationFactor) break;
            }
        }
        if (stored < replicationFactor)
            cout << " Warning: Not enough active nodes for full replication.\n";
    }

    void downloadFile(const string &filename) {
        cout << "\n Downloading '" << filename << "'...\n";
        for (auto node : nodes) {
            if (node->active && node->hasFile(filename)) {
                cout << " File retrieved from " << node->name
                     << " : " << node->getFile(filename) << endl;
                return;
            }
        }
        cout << " File not available (all replicas lost or nodes down)." << endl;
    }

    void listFiles() {
        cout << "\n File Distribution:\n";
        for (auto node : nodes) {
            cout << node->name << " (" << (node->active ? "Active" : "Down") << "): ";
            if (node->files.empty()) cout << "[Empty]";
            for (auto &f : node->files)
                cout << f.first << " ";
            cout << endl;
        }
    }

    void failNode(int index) {
        if (index >= 0 && index < nodes.size()) {
            if (!nodes[index]->active) {
                cout << nodes[index]->name << " is already down.\n";
                return;
            }
            nodes[index]->active = false;
            cout << " " << nodes[index]->name << " has FAILED.\n";
        }
    }

    void recoverNode(int index) {
        if (index >= 0 && index < nodes.size()) {
            if (nodes[index]->active) {
                cout << nodes[index]->name << " is already active.\n";
                return;
            }
            nodes[index]->active = true;
            cout << " " << nodes[index]->name << " is RECOVERED.\n";
        }
    }

    void repairFaults() {
        cout << "\n Repairing Faults (Re-replicating lost files)...\n";
        map<string, int> fileCount;

        // Count how many active nodes have each file
        for (auto node : nodes) {
            if (!node->active) continue;
            for (auto &f : node->files)
                fileCount[f.first]++;
        }

        // Re-replicate missing files
        for (auto &pair : fileCount) {
            string filename = pair.first;
            int copies = pair.second;

            if (copies < replicationFactor) {
                cout << " Re-replicating " << filename << " (" << copies
                     << "/" << replicationFactor << ")\n";
                string data = "";

                // Get data from one of the active nodes
                for (auto node : nodes) {
                    if (node->active && node->hasFile(filename)) {
                        data = node->getFile(filename);
                        break;
                    }
                }

                // Copy to other nodes until replication factor met
                for (auto node : nodes) {
                    if (copies >= replicationFactor) break;
                    if (node->active && !node->hasFile(filename)) {
                        node->storeFile(filename, data);
                        copies++;
                    }
                }
            }
        }

        cout << " Fault repair completed.\n";
    }

    int totalNodes() { return nodes.size(); }
};

// ===================== MAIN PROGRAM =====================
int main() {
    cout << "=============================================\n";
    cout << "     Mini Distributed File System\n";
    cout << "     With Fault Tolerance Simulation\n";
    cout << "=============================================\n";

    int numNodes = 4;
    int replication = 2;

    DistributedFileSystem dfs(numNodes, replication);

    int choice;
    string filename, data;
    int nodeIndex;

    do {
        cout << "\n---------------- MENU ----------------\n";
        cout << "1. Upload File\n";
        cout << "2. Download File\n";
        cout << "3. Fail Node\n";
        cout << "4. Recover Node\n";
        cout << "5. Repair Faults\n";
        cout << "6. List Files\n";
        cout << "7. Exit\n";
        cout << "--------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename: ";
            cin >> filename;
            cout << "Enter file content: ";
            cin.ignore();
            getline(cin, data);
            dfs.uploadFile(filename, data);
            break;

        case 2:
            cout << "Enter filename to download: ";
            cin >> filename;
            dfs.downloadFile(filename);
            break;

        case 3:
            cout << "Enter node number to fail (1-" << dfs.totalNodes() << "): ";
            cin >> nodeIndex;
            dfs.failNode(nodeIndex - 1);
            break;

        case 4:
            cout << "Enter node number to recover (1-" << dfs.totalNodes() << "): ";
            cin >> nodeIndex;
            dfs.recoverNode(nodeIndex - 1);
            break;

        case 5:
            dfs.repairFaults();
            break;

        case 6:
            dfs.listFiles();
            break;

        case 7:
            cout << "Exiting... Thank you!\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
