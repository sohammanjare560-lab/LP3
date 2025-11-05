#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Define a class for items
class Item {
public:
    int value;
    int weight;

    // Constructor to initialize an item
    Item(int v, int w) {
        value = v;
        weight = w;
    }
};

// Comparator function to sort items by value/weight ratio
bool cmp(const Item &a, const Item &b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;  // Sort in descending order
}

// Function to compute maximum value using fractional knapsack
double fractionalKnapsack(int W, vector<Item> &arr, int n) {
    // Step 1: Sort items based on value/weight ratio
    sort(arr.begin(), arr.end(), cmp);

    double finalValue = 0.0; // Result (maximum value)

    // Step 2: Pick items
    for (int i = 0; i < n; i++) {
        if (arr[i].weight <= W) {
            // Take full item
            W -= arr[i].weight;
            finalValue += arr[i].value;
        } else {
            // Take fractional part of the item
            double fraction = (double)W / arr[i].weight;
            finalValue += arr[i].value * fraction;
            break;  // Knapsack is full
        }
    }
    return finalValue;
}

// Main function
int main() {
    int n, W;

    cout << "Enter the number of items: ";
    cin >> n;

    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    vector<Item> arr;
    cout << "\nEnter the value and weight of each item:\n";

    for (int i = 0; i < n; i++) {
        int value, weight;
        cout << "Item " << i + 1 << " (value weight): ";
        cin >> value >> weight;
        arr.push_back(Item(value, weight));
    }

    double maxValue = fractionalKnapsack(W, arr, n);

    cout << "\nMaximum value we can obtain = " << maxValue << endl;

    return 0;
}
