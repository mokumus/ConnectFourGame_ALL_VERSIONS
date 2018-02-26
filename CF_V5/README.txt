-Notes:
* I assumed that game should still be playable with standart rules, so I implemented the virtual functions for abstract class too.
* Play functions(Comp move, user move) are independent from the type of the ConnectFour object.
* ostream operator for cell class is implemented in the header file, i was getting linker error when trying implement operator in
  the cpp file.
* Base destructor is suffice for all derived classes, but still declared as virtual for good practice.

-New methods:
* New class variable added to cell.h to hold number of moves made, and it's manipulative methods also added.


-Edited functions:
* playGame() edited to take board height and size as input rather than filename. Also overriden for CFUndo and isn't static anymore.
* isWon edited to provide new rules for derived objects.


-New Command: UNDO
* UNDO Command takes back last move made by previous player, and changes turn to previous player. If there are no moves to undo an
  error text is given and program waits for a MOVE/SAVE/LOAD input.



- Removed features from HW4:
* Comparison operators for ConnectFour classes.
* Increment, decrement, comparison and istream operators for Cell class.
* Living cell count.
* Multiplayer option.
* File reading constructor.


MUHAMMED OKUMUS
151044017
