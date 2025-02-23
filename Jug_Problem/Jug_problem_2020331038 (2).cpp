#include <bits/stdc++.h>
using namespace std;

#define ll long long

// Function to check if we can measure Z using jugs X and Y
bool canMeasureWater(int x, int y, int z) {
    if (z > x + y) return false;  // If Z is greater than the combined capacity, it's not possible
    if (z == 0 || z == x || z == y || z == (x + y)) return true;
    return (z % __gcd(x, y) == 0);  // GCD condition for when it's possible
}

// Function to print each step
void printStep(int l, int r, int prevL, int prevR) {
    if (l > prevL && r == prevR) 
        cout << "Filled Jug1 from external source → (Jug1: " << l << "L, Jug2: " << r << "L)\n";
    else if (r > prevR && l == prevL) 
        cout << "Filled Jug2 from external source → (Jug1: " << l << "L, Jug2: " << r << "L)\n";
    else if (l < prevL && r == prevR) 
        cout << "Emptied Jug1 → (Jug1: " << l << "L, Jug2: " << r << "L)\n";
    else if (r < prevR && l == prevL) 
        cout << "Emptied Jug2 → (Jug1: " << l << "L, Jug2: " << r << "L)\n";
    else if (l > prevL && r < prevR) 
        cout << "Poured water from Jug2 into Jug1 → (Jug1: " << l << "L, Jug2: " << r << "L)\n";
    else if (r > prevR && l < prevL) 
        cout << "Poured water from Jug1 into Jug2 → (Jug1: " << l << "L, Jug2: " << r << "L)\n";
}

void solve() {
    int X, Y, Z;
    cin >> X >> Y >> Z;

    if (X < Y) swap(X, Y); // Ensure X is the larger jug

    if (!canMeasureWater(X, Y, Z)) {
        cout << "❌ Not possible to measure " << Z << " liters using " << X << "L and " << Y << "L jugs.\n";
        return;
    }

    queue<pair<int, int>> q;
    map<pair<int, int>, pair<int, int>> parent;
    q.push({0, 0}); // Start with both jugs empty
    parent[{0, 0}] = {-1, -1};

    while (!q.empty()) {
        auto [l, r] = q.front();
        q.pop();

        // If we have the desired total in both jugs, return the process
        if (l + r == Z) {
            vector<pair<int, int>> path;
            while (parent[{l, r}] != make_pair(-1, -1)) {
                path.push_back({l, r});
                tie(l, r) = parent[{l, r}];
            }
            path.push_back({0, 0});
            reverse(path.begin(), path.end());

            cout << "✅ Successfully measured " << Z << " liters!\n";
            cout << "🔹 Process:\n";
            for (size_t i = 1; i < path.size(); i++) {
                int prevL = path[i - 1].first, prevR = path[i - 1].second;
                int currL = path[i].first, currR = path[i].second;
                printStep(currL, currR, prevL, prevR);
            }
            return;
        }

        // Generate the next possible states
        vector<pair<int, int>> nextStates = {
            {X, r}, {l, Y}, {0, r}, {l, 0},  // Fill & Empty operations
            {max(0, l - (Y - r)), min(Y, r + l)},  // Pour Jug1 → Jug2
            {min(X, l + r), max(0, r - (X - l))}   // Pour Jug2 → Jug1
        };

        // Check all possible next states
        for (auto &state : nextStates) {
            if (parent.count(state) == 0) {
                parent[state] = {l, r};
                q.push(state);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tt = 1;
    // cin >> tt; // Uncomment for multiple test cases
    while (tt--) {
        solve();
    }

    return 0;
}
