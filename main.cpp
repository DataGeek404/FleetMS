#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

// Helper function to clear input buffer
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

class Vehicle {
public:
    int vehicleId;
    int mileage;
    std::string make;
    std::string model;
    std::string numberPlate;
    int year;

    void addVehicle();
    void updateMileage(int newMileage);
    void getDetails();
    void assignDriver(int driverId);
    static void viewAllVehicles();
};

void Vehicle::addVehicle() {
    std::cout << "Enter Vehicle ID: ";
    std::cin >> vehicleId;
    clearInputBuffer(); // Clear buffer to avoid issues with next inputs

    std::cout << "Enter Mileage: ";
    std::cin >> mileage;
    clearInputBuffer();

    std::cout << "Enter Make: ";
    std::getline(std::cin, make);

    std::cout << "Enter Model: ";
    std::getline(std::cin, model);

    std::cout << "Enter Number Plate: ";
    std::getline(std::cin, numberPlate);

    std::cout << "Enter Year: ";
    std::cin >> year;
    clearInputBuffer();

    std::ofstream outFile("vehicles.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << vehicleId << "," << mileage << "," << make << "," << model << "," << numberPlate << "," << year << "\n";
        outFile.close();
        std::cout << "Vehicle added to file.\n";
    } else {
        std::cerr << "Unable to open vehicles.txt\n";
    }
}

void Vehicle::updateMileage(int newMileage) {
    std::ifstream inFile("vehicles.txt");
    std::ofstream outFile("temp.txt");
    std::string line;

    if (inFile.is_open() && outFile.is_open()) {
        while (getline(inFile, line)) {
            std::istringstream iss(line);
            int id, mileage, year;
            std::string make, model, plate;
            char comma;

            iss >> id >> comma >> mileage >> comma;
            getline(iss, make, ',');
            getline(iss, model, ',');
            getline(iss, plate, ',');
            iss >> year;

            if (id == vehicleId) {
                mileage = newMileage;
            }
            outFile << id << "," << mileage << "," << make << "," << model << "," << plate << "," << year << "\n";
        }
        inFile.close();
        outFile.close();
        remove("vehicles.txt");
        rename("temp.txt", "vehicles.txt");
        std::cout << "Mileage updated in file.\n";
    } else {
        std::cerr << "Unable to open vehicles.txt or temp.txt\n";
    }
}

void Vehicle::getDetails() {
    std::ifstream inFile("vehicles.txt");
    std::string line;
    bool found = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            std::istringstream iss(line);
            int id;
            std::string details;

            getline(iss, details);
            if (std::stoi(details.substr(0, details.find(','))) == vehicleId) {
                std::cout << "Vehicle Details: " << details << "\n";
                found = true;
                break;
            }
        }
        inFile.close();
        if (!found) std::cout << "Vehicle not found.\n";
    } else {
        std::cerr << "Unable to open vehicles.txt\n";
    }
}

void Vehicle::viewAllVehicles() {
    std::ifstream inFile("vehicles.txt");
    std::string line;
    if (inFile.is_open()) {
        std::cout << "All Vehicles:\n";
        while (getline(inFile, line)) {
            std::cout << line << "\n";
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open vehicles.txt\n";
    }
}

void Vehicle::assignDriver(int driverId) {
    std::cout << "Driver " << driverId << " assigned to Vehicle " << vehicleId << "\n";
    std::ofstream outFile("assignments.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "Vehicle " << vehicleId << " assigned to Driver " << driverId << "\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open assignments.txt\n";
    }
}

class Driver {
public:
    int driverId;
    std::string licenseNo;
    std::string name;

    void addDriver();
    void startTrip();
    void endTrip();
    void assignVehicle(int vehicleId);
    static void viewAllDrivers();
};

void Driver::addDriver() {
    std::cout << "Enter Driver ID: ";
    std::cin >> driverId;
    clearInputBuffer();

    std::cout << "Enter License No: ";
    std::getline(std::cin, licenseNo);

    std::cout << "Enter Name: ";
    std::getline(std::cin, name);

    std::ofstream outFile("drivers.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << driverId << "," << licenseNo << "," << name << "\n";
        outFile.close();
        std::cout << "Driver added to file.\n";
    } else {
        std::cerr << "Unable to open drivers.txt\n";
    }
}

void Driver::viewAllDrivers() {
    std::ifstream inFile("drivers.txt");
    std::string line;
    if (inFile.is_open()) {
        std::cout << "All Drivers:\n";
        while (getline(inFile, line)) {
            std::cout << line << "\n";
        }
        inFile.close();
    } else {
        std::cerr << "Unable to open drivers.txt\n";
    }
}

void Driver::startTrip() {
    std::cout << "Trip started by Driver " << driverId << "\n";
}

void Driver::endTrip() {
    std::cout << "Trip ended by Driver " << driverId << "\n";
}

void Driver::assignVehicle(int vehicleId) {
    std::cout << "Driver " << driverId << " assigned to Vehicle " << vehicleId << "\n";
    std::ofstream outFile("assignments.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "Driver " << driverId << " assigned to Vehicle " << vehicleId << "\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open assignments.txt\n";
    }
}

class Trip {
public:
    int tripId;
    int vehicleId;
    int driverId;
    std::string startLocation;
    std::string stopLocation;
    std::string startTime;
    std::string endTime;

    void startTrip();
    void endTrip();
    void calculateDistance();
    void recordTrip();
};

void Trip::startTrip() {
    startTime = "2024-11-10 10:00:00";
    std::cout << "Trip started at " << startTime << "\n";
}

void Trip::endTrip() {
    endTime = "2024-11-10 14:00:00";
    std::cout << "Trip ended at " << endTime << "\n";
}

void Trip::calculateDistance() {
    double distance = 100.0;
    std::cout << "Calculated distance for Trip " << tripId << " is " << distance << " km.\n";

    std::ofstream outFile("trip_distances.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << "Trip " << tripId << ": Distance = " << distance << " km\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open trip_distances.txt\n";
    }
}

void Trip::recordTrip() {
    std::ofstream outFile("trips.txt", std::ios::app);
    if (outFile.is_open()) {
        outFile << tripId << "," << vehicleId << "," << driverId << "," << startLocation << "," << stopLocation << "," << startTime << "," << endTime << "\n";
        outFile.close();
        std::cout << "Trip recorded in file.\n";
    } else {
        std::cerr << "Unable to open trips.txt\n";
    }
}

void displayMenu() {
    std::cout << "\nFleet Management System Menu:\n";
    std::cout << "1. Add Vehicle\n";
    std::cout << "2. Update Vehicle Mileage\n";
    std::cout << "3. Get Vehicle Details\n";
    std::cout << "4. View All Vehicles\n";
    std::cout << "5. Add Driver\n";
    std::cout << "6. View All Drivers\n";
    std::cout << "7. Start Trip\n";
    std::cout << "8. End Trip\n";
    std::cout << "9. Record Trip\n";
    std::cout << "10. Calculate Distance\n";
    std::cout << "11. Assign Vehicle to Driver\n";
    std::cout << "12. Assign Driver to Vehicle\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    int choice;
    Vehicle vehicle;
    Driver driver;
    Trip trip;

    do {
        displayMenu();
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                vehicle.addVehicle();
                break;
            case 2: {
                std::cout << "Enter Vehicle ID and new Mileage: ";
                std::cin >> vehicle.vehicleId >> vehicle.mileage;
                clearInputBuffer();
                vehicle.updateMileage(vehicle.mileage);
                break;
            }
            case 3: {
                std::cout << "Enter Vehicle ID to get details: ";
                std::cin >> vehicle.vehicleId;
                clearInputBuffer();
                vehicle.getDetails();
                break;
            }
            case 4:
                Vehicle::viewAllVehicles();
                break;
            case 5:
                driver.addDriver();
                break;
            case 6:
                Driver::viewAllDrivers();
                break;
            case 7: {
                std::cout << "Enter Driver ID to start trip: ";
                std::cin >> driver.driverId;
                clearInputBuffer();
                driver.startTrip();
                break;
            }
            case 8: {
                std::cout << "Enter Driver ID to end trip: ";
                std::cin >> driver.driverId;
                clearInputBuffer();
                driver.endTrip();
                break;
            }
            case 9: {
                std::cout << "Enter Trip ID: ";
                std::cin >> trip.tripId;
                clearInputBuffer();

                std::cout << "Enter Vehicle ID: ";
                std::cin >> trip.vehicleId;
                clearInputBuffer();

                std::cout << "Enter Driver ID: ";
                std::cin >> trip.driverId;
                clearInputBuffer();

                std::cout << "Enter Start Location: ";
                std::getline(std::cin, trip.startLocation);

                std::cout << "Enter Stop Location: ";
                std::getline(std::cin, trip.stopLocation);

                std::cout << "Enter Start Time: ";
                std::getline(std::cin, trip.startTime);

                std::cout << "Enter End Time: ";
                std::getline(std::cin, trip.endTime);

                trip.recordTrip();
                break;
            }
            case 10: {
                std::cout << "Enter Trip ID to calculate distance: ";
                std::cin >> trip.tripId;
                clearInputBuffer();
                trip.calculateDistance();
                break;
            }
            case 11: {
                std::cout << "Enter Vehicle ID to assign to Driver: ";
                int vehicleId;
                std::cin >> vehicleId;
                clearInputBuffer();

                std::cout << "Enter Driver ID: ";
                int driverId;
                std::cin >> driverId;
                clearInputBuffer();

                driver.driverId = driverId;
                driver.assignVehicle(vehicleId);
                break;
            }
            case 12: {
                std::cout << "Enter Driver ID to assign to Vehicle: ";
                int driverId;
                std::cin >> driverId;
                clearInputBuffer();

                std::cout << "Enter Vehicle ID: ";
                int vehicleId;
                std::cin >> vehicleId;
                clearInputBuffer();

                vehicle.vehicleId = vehicleId;
                vehicle.assignDriver(driverId);
                break;
            }
            case 0:
                std::cout << "Exiting Fleet Management System.\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
