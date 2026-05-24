# EcoRide 🚗
EcoRide is a Qt-based ride-sharing application built in C++ that allows **drivers** to post rides and **riders** to accept or propose fares.  
It demonstrates file handling, GUI development, and basic ride-booking logic.
##  Features
### Rider Dashboard
- View available rides (driver, origin, destination, fare).
- Accept rides (updates status in `rides.txt`).
- Propose a counter fare (stored in `proposals.txt`).
- View accepted rides.
- Cancel accepted rides.
- Navigate back to main menu.
### Driver Dashboard
- Post new rides (origin, destination, fare).
- View rides accepted by riders.
- View fare proposals and accept them.
- Cancel pending rides.
- Navigate back to main menu.
## Tech Stack
- **Language:** C++  
- **Framework:** Qt (Widgets, Layouts, Signals/Slots)  
- **Storage:** Text files (`rides.txt`, `proposals.txt`)
  
##  File Structure
- `rides.txt` → Stores driver rides with status (`Pending`, `Accepted`, `Cancelled`) and rider info.  
- `proposals.txt` → Stores rider fare proposals.  
- `mainwindow.cpp` → Entry point and navigation.  
- `riderdashboard.cpp` → Rider interface logic.  
- `driverdashboard.cpp` → Driver interface logic.  

##  How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/iiqra0436-wq/EcoRide.git
