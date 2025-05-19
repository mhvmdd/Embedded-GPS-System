# 🏨 Hotel Booking System

A comprehensive Java-based hotel management system that allows guests to book rooms, manage reservations, and handle payments efficiently.

## ✨ Features

### 👥 User Management
- Guest registration and authentication
- Admin panel for system management
- Secure password handling
- User profile management

### 🛏️ Room Management
- Multiple room types (Standard, Deluxe, Suite)
- Room availability tracking
- Detailed room information display
- Room features and amenities tracking

### 📅 Booking System
- Real-time room availability checking
- Flexible check-in/check-out dates
- Booking status tracking (Booked, Checked-in, Checked-out, Cancelled)
- Booking history for guests

### 💳 Payment Processing
- Multiple payment methods (Cash, Credit Card, Debit Card, PayPal)
- Payment status tracking
- Promo code support
- Refund handling

### 🎯 Additional Features
- Beautiful GUI using JavaFX
- Responsive design
- Real-time availability updates
- Comprehensive error handling

## 🛠️ Technical Details

### Built With
- Java 8+
- JavaFX for GUI
- Object-Oriented Programming principles
- Design Patterns implementation

### Project Structure
```
src/main/java/org/advcomprog/hotelbooking/hotelbookingsystem/
├── User.java (Abstract)
├── Guest.java
├── Admin.java
├── Room.java (Abstract)
├── StandardRoom.java
├── DeluxeRoom.java
├── Suite.java (Abstract)
├── JuniorSuite.java
├── LuxuriousSuite.java
├── Booking.java
├── Payment.java
├── Hotel.java
└── HotelBookingSystem.java
```

## 📋 UML Diagram
# 🏨 Hotel Booking System

// ... existing code ...

## 📋 UML Diagram
```mermaid
classDiagram
    class User {
        <<abstract>>
        -String userId
        -String name
        -String email
        -String password
        +getUserId()
        +getName()
        +getEmail()
        +getPassword()
        +verifyPassword()
        +getRole()
    }
    
    class Guest {
        +displayInfo()
        +getRole()
    }
    
    class Admin {
        +displayInfo()
        +getRole()
    }
    
    class Room {
        <<abstract>>
        -String roomNumber
        -int capacity
        -double priceForNight
        -boolean isAvailable
        +displayInfo()
        +getRoomNumber()
        +getPrice()
    }
    
    class StandardRoom {
        +displayInfo()
    }
    
    class DeluxeRoom {
        +displayInfo()
    }
    
    class Suite {
        <<abstract>>
        +displayInfo()
    }
    
    class JuniorSuite {
        +displayInfo()
    }
    
    class LuxuriousSuite {
        +displayInfo()
    }
    
    class Booking {
        -String bookingId
        -Guest guest
        -Room room
        -LocalDate checkIn
        -LocalDate checkOut
        +displayInfo()
        +getBookingId()
    }
    
    class Payment {
        -String paymentId
        -String bookingId
        -double amount
        -PaymentMethod method
        -PaymentStatus status
        +displayInfo()
        +getPaymentId()
    }
    
    class Hotel {
        -String name
        -ArrayList~Room~ rooms
        -ArrayList~User~ guests
        -ArrayList~User~ admins
        -ArrayList~Booking~ bookings
        -ArrayList~Payment~ payments
        +addRoom()
        +removeRoom()
        +createBooking()
        +cancelBooking()
    }
    
    User <|-- Guest
    User <|-- Admin
    Room <|-- StandardRoom
    Room <|-- DeluxeRoom
    Room <|-- Suite
    Suite <|-- JuniorSuite
    Suite <|-- LuxuriousSuite
    Booking --> Guest
    Booking --> Room
    Payment --> Booking
    Hotel --> Room
    Hotel --> User
    Hotel --> Booking
    Hotel --> Payment
```

// ... existing code ...

## 🚀 Getting Started

### Prerequisites
- Java Development Kit (JDK) 8 or higher
- JavaFX SDK
- Your favorite IDE (IntelliJ IDEA, Eclipse, etc.)

### Installation
1. Clone the repository
```bash
git clone https://github.com/yourusername/hotel-booking-system.git
```

2. Open the project in your IDE

3. Build and run the project
```bash
javac HotelBookingSystem.java
java HotelBookingSystem
```

## 👨‍💻 Usage

### For Guests
1. Register a new account
2. Browse available rooms
3. Select dates and make a booking
4. Choose payment method
5. Receive booking confirmation

### For Admins
1. Login to admin panel
2. Manage rooms and bookings
3. Handle guest registrations
4. Process payments and refunds
5. Apply promotional codes

## 🤝 Contributing
Contributions are welcome! Please feel free to submit a Pull Request.

## 📝 License
This project is licensed under the MIT License - see the LICENSE file for details.

## 👥 Authors
- Your Name - Initial work

## 🙏 Acknowledgments
- Thanks to all contributors
- Inspired by real-world hotel management systems
