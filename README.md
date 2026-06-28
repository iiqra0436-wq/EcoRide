# EcoRide 🚗

EcoRide is a Qt-based ride-sharing desktop application built in C++ that allows **drivers** to post rides and **riders** to accept or propose fares. It demonstrates object-oriented programming, file handling, GUI development, and core ride-booking logic.

---
## Demo
 
https://github.com/user-attachments/assets/95b3b652-3dea-47b7-a4ad-86f540ffcaf5

## Screenshots

| Login | Driver Dashboard | Rider Dashboard |
|-------|-----------------|-----------------|
|![image alt](https://github.com/iiqra0436-wq/EcoRide/blob/33b023aa33ce1dce7cfe66c5171ba70511acc38e/login.png )| ![image alt](https://github.com/iiqra0436-wq/EcoRide/blob/33b023aa33ce1dce7cfe66c5171ba70511acc38e/driver.png) |![image alt](https://github.com/iiqra0436-wq/EcoRide/blob/33b023aa33ce1dce7cfe66c5171ba70511acc38e/rider.png) |

---

## Features

### 🧑‍💼 Rider Dashboard
- View available rides (driver, origin, destination, fare)
- Accept rides — updates status in `rides.txt`
- Propose a counter fare — stored in `proposals.txt`
- View accepted rides
- Cancel accepted rides
- Navigate back to main menu

### 🚘 Driver Dashboard
- Post new rides (origin, destination, fare)
- View rides accepted by riders
- View and accept fare proposals from riders
- Cancel pending rides
- Navigate back to main menu

---

## Tech Stack

| Layer | Technology |
|---|---|
| Language | C++ |
| GUI Framework | Qt (Widgets, Layouts, Signals & Slots) |
| Storage | Text files (`rides.txt`, `proposals.txt`) |

---

## File Structure

```
EcoRide/
├── main.cpp                  # Entry point
├── mainwindow.cpp/.h         # Main navigation window
├── riderdashboard.cpp/.h     # Rider interface and logic
├── driverdashboard.cpp/.h    # Driver interface and logic
├── rides.txt                 # Stores ride entries with status (Pending / Accepted / Cancelled)
├── proposals.txt             # Stores rider fare proposals
└── docs/
    ├── proposal.pdf          # Project proposal presentation
    └── report.pdf            # Final project report
```

---

## How to Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/iiqra0436-wq/EcoRide.git
   cd EcoRide
   ```

2. **Open in Qt Creator**
   - File → Open Project → select the `.pro` file

3. **Build and run**
   - Press `Ctrl + R` or click the green Run button

> Make sure Qt (version 5 or 6) is installed. `rides.txt` and `proposals.txt` will be auto-created on first run.

---

## Future Improvements

- Add user login and authentication
- Replace text file storage with SQLite database
- Implement real-time ride matching
- Add a map view for ride routes
- Package as a standalone executable

---

## What I Learned

- Applying OOP concepts (classes, encapsulation, inheritance) in a real project
- Building GUI applications with Qt Widgets and signal/slot mechanism
- Managing persistent data with file I/O in C++
- Structuring a multi-screen desktop application

---

## Author

**Iqra Iqbal** — BS Software Engineering, Bahria University  
📧 iiqra0436@gmail.com · 🔗 [GitHub](https://github.com/iiqra0436-wq)
