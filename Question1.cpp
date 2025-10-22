// Question 1:
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cctype>

struct Queue10 {
    static const int CAP = 10;
    int data[CAP] = {0};
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
    std::string toString() const {
        if (empty()) return "[]";
        std::string s = "[";
        for (int i = 0; i < size; ++i) {
            int idx = (head + i) % CAP;
            s += std::to_string(data[idx]);
            if (i + 1 < size) s += ", ";
        }
        s += "]";
        return s;
    }
};

static inline bool readLine(std::ifstream &in, std::string &line) {
    if (!std::getline(in, line)) return false;
    // trim both ends (ASCII whitespace)
    size_t l = 0;
    while (l < line.size() && std::isspace(static_cast<unsigned char>(line[l]))) ++l;
    size_t r = line.size();
    while (r > l && std::isspace(static_cast<unsigned char>(line[r - 1]))) --r;
    line = line.substr(l, r - l);
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream in("input.txt");
    if (!in) { std::cerr << "Missing input.txt in the working directory.\n"; return 1; }
    std::ofstream out("output.txt");
    if (!out) { std::cerr << "Cannot open output.txt for writing.\n"; return 1; }

    Queue10 q;
    std::string line;
    while (readLine(in, line)) {
        if (line.empty()) continue;

        if (line == "Add" || line == "add" || line == "ADD") {
            std::string next;
            if (!readLine(in, next)) break;
            out << "Add requested.\n";
            try {
                size_t pos = 0;
                long long val_ll = std::stoll(next, &pos);
                if (pos != next.size()) throw std::invalid_argument("trailing");
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
