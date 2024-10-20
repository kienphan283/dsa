#include <iostream>
using namespace std;

// Function to move a disk from one peg to another
void moveDisk(int n, char from_peg, char to_peg, char aux_peg) {
    if (n == 1) {
        cout << "Move disk 1 from peg " << from_peg << " to peg " << to_peg << endl;
        return;
    }
    // Move n-1 disks from 'from_peg' to 'aux_peg', using 'to_peg' as auxiliary
    moveDisk(n - 1, from_peg, aux_peg, to_peg);
    // Move the last disk from 'from_peg' to 'to_peg'
    cout << "Move disk " << n << " from peg " << from_peg << " to peg " << to_peg << endl;
    // Move n-1 disks from 'aux_peg' to 'to_peg', using 'from_peg' as auxiliary
    moveDisk(n - 1, aux_peg, to_peg, from_peg);
}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    cout << "The steps to move the disks:\n";
    moveDisk(n, 'A', 'C', 'B');  // A is the starting peg, C is the destination peg, B is the auxiliary peg
    return 0;
}
