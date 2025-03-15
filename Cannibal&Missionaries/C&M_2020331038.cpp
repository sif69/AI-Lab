#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <tuple>
#include <iomanip>

using namespace std;

typedef tuple<int, int, char, int, int> State;

bool is_valid(State state) {
    int ml, cl, mr, cr;
    char b;
    tie(ml, cl, b, mr, cr) = state;

    if (ml < 0 || cl < 0 || mr < 0 || cr < 0)
        return false;

    if ((ml > 0 && ml < cl) || (mr > 0 && mr < cr))
        return false;

    return true;
}

vector<pair<State, pair<int, int>>> get_successors(State state) {
    int ml, cl, mr, cr;
    char b;
    tie(ml, cl, b, mr, cr) = state;

    vector<pair<int, int>> moves = {{1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}};
    vector<pair<State, pair<int, int>>> successors;

    for (auto move : moves) {
        int mm = move.first, cm = move.second;
        State new_state;

        if (b == 'L') {
            new_state = make_tuple(ml - mm, cl - cm, 'R', mr + mm, cr + cm);
        } else {
            new_state = make_tuple(ml + mm, cl + cm, 'L', mr - mm, cr - cm);
        }

        if (is_valid(new_state)) {
            successors.push_back({new_state, {mm, cm}});
        }
    }

    return successors;
}

struct Node {
    State state;
    pair<int, int> move;
    vector<Node> path;

    Node(State s, pair<int, int> m, vector<Node> p) : state(s), move(m), path(p) {}
};

vector<Node> solve_missionaries_cannibals() {
    State initial_state = make_tuple(3, 3, 'L', 0, 0);
    State goal_state = make_tuple(0, 0, 'R', 3, 3);

    queue<Node> q;
    set<State> visited;
    q.push(Node(initial_state, {0, 0}, {}));

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (visited.count(current.state))
            continue;

        visited.insert(current.state);

        if (current.state == goal_state) {
            vector<Node> solution = current.path;
            solution.push_back(current);
            return solution;
        }

        for (auto successor : get_successors(current.state)) {
            vector<Node> new_path = current.path;
            new_path.push_back(current);
            q.push(Node(successor.first, successor.second, new_path));
        }
    }

    return {};
}

void print_solution(const vector<Node>& solution) {
    cout << "Missionaries and Cannibals Problem\n";
    cout << "-----------------------------------\n\n";

    for (const auto& node : solution) {
        int ml, cl, mr, cr;
        char b;
        tie(ml, cl, b, mr, cr) = node.state;
        int mm = node.move.first, cm = node.move.second;

        for (int j = 0; j < ml; j++) cout << "M ";
        for (int j = 0; j < cl; j++) cout << "C ";
        cout << setw(13 - 2 * (ml + cl)) << " ";

        if (b == 'L') {
            cout << "BOAT-L[";
        } else {
            cout << "------------BOAT-R[";
        }
        if (mm > 0) cout << mm << "M";
        if (cm > 0) cout << ((mm > 0) ? "," : "") << cm << "C";
        if (mm == 0 && cm == 0) cout << " ";
        cout << "]";

        if (b == 'L') {
            cout << "-------------";
        }
        cout << " ";
        for (int j = 0; j < mr; j++) cout << "M ";
        for (int j = 0; j < cr; j++) cout << "C ";

        cout << endl;
    }
}

int main() {
    vector<Node> solution = solve_missionaries_cannibals();
    if (!solution.empty()) {
        print_solution(solution);
    } else {
        cout << "No solution found." << endl;
    }
    return 0;
}
