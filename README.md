# EcoRide 🚗

EcoRide is a desktop ride-sharing application built with C++ and the Qt Framework. It enables drivers to post rides while riders can browse, accept, or negotiate fares through an intuitive graphical interface. The project showcases Object-Oriented Programming (OOP), GUI development, file handling, and desktop application design.

## Demo

https://github.com/user-attachments/assets/95b3b652-3dea-47b7-a4ad-86f540ffcaf5

## Screenshots

| Login | Driver Dashboard | Rider Dashboard |
|-------|-----------------|-----------------|
|![image alt](https://github.com/iiqra0436-wq/EcoRide/blob/33b023aa33ce1dce7cfe66c5171ba70511acc38e/login.png )| ![image alt](https://github.com/iiqra0436-wq/EcoRide/blob/33b023aa33ce1dce7cfe66c5171ba70511acc38e/driver.png) |![image alt](https://github.com/iiqra0436-wq/EcoRide/blob/33b023aa33ce1dce7cfe66c5171ba70511acc38e/rider.png) |

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
- **Language:** C++
- **Framework:** Qt (Widgets, Signals & Slots)
- **Programming Concepts:** Object-Oriented Programming (OOP)
- **Data Storage:** Text File Handling

---
## How to Run

1. Clone the repository:

   ```bash
   git clone https://github.com/iiqra0436-wq/EcoRide.git
   cd EcoRide
   ```
2. Open the project (`.pro` file) in **Qt Creator**.
3. Build and run the application.
> **Requirements:** Qt 5 or Qt 6 installed.


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
