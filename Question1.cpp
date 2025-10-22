// Question 1:
#include <bits/stdc++.h>
using namespace std;

struct Queue10 {
    static constexpr int CAP = 10;
    int data[CAP]{};
    int head = 0;  // front index
    int tail = 0;  // next insert index
    int size = 0;  // current count
    bool empty() const { return size == 0; }
    bool full()  const { return size == CAP; }

    bool enqueue(int x) {                 // capacity constraint
        if (full()) return false;
        data[tail] = x;
        tail = (tail + 1) % CAP;
        ++size;
        return true;
    }
    bool dequeue(int &out) {              // empty-queue safety
        if (empty()) return false;
        out = data[head];
        head = (head + 1) % CAP;
        --size;
        return true;
    }
    string toString() const {
        if (empty()) return "[]";
        string s = "[";
        for (int i = 0; i < size; ++i) {
            int idx = (head + i) % CAP;
            s += to_string(data[idx]);
            if (i + 1 < size) s += ", ";
        }
        s += "]";
        return s;
    }
};

static bool readLine(ifstream &in, string &line) {
    if (!std::getline(in, line)) return false;
    auto l = line.find_first_not_of(" \t\r\n");
    auto r = line.find_last_not_of(" \t\r\n");
    if (l == string::npos) { line.clear(); return true; }  // ignore blank lines
    line = line.substr(l, r - l + 1);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in("input.txt");
    if (!in) { cerr << "Missing input.txt in the working directory.\n"; return 1; }
    ofstream out("output.txt");
    if (!out) { cerr << "Cannot open output.txt for writing.\n"; return 1; }

    Queue10 q;
    string line;
    while (readLine(in, line)) {
        if (line.empty()) continue;

        if (line == "Add" || line == "add" || line == "ADD") {
            string next;
            if (!readLine(in, next)) break;
            out << "Add requested.\n";
            try {
                size_t pos = 0;
                long long val_ll = stoll(next, &pos);
                if (pos != next.size()) throw invalid_argument("trailing");
                int val = static_cast<int>(val_ll);
                if (q.full()) {
                    out << "Queue is full. Cannot add: " << val << "\n";
                } else {
                    q.enqueue(val);
                    out << "Enqueued: " << val << "\n";
                }
            } catch (...) {
                out << "Invalid ID. Skipped: " << next << "\n";
            }
            out << "Queue: " << q.toString() << "\n";

        } else if (line == "Delete" || line == "delete" || line == "DELETE") {
            out << "Delete requested.\n";
            int removed = 0;
            if (!q.dequeue(removed)) {
                out << "Queue is empty. Cannot delete.\n";
            } else {
                out << "Dequeued: " << removed << "\n";
            }
            out << "Queue: " << q.toString() << "\n";

        } else if (line == "Exit" || line == "exit" || line == "EXIT") {
            out << "Exit requested.\n";
            out << "Program finished.\n";
            break;

        } else {
            out << "Unknown command: " << line << "\n";
            out << "Queue: " << q.toString() << "\n";
        }
    }
    return 0;
}
