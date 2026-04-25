#ifndef HOSPITALMANAGEMENT_HOSPITALFUNCS_H
#define HOSPITALMANAGEMENT_HOSPITALFUNCS_H

#include <stdbool.h>

typedef struct {
    char name[100];
    char specialisation[100];
    char contactInformation[100];
    bool availability;
} Doctor;

typedef struct {
    char name[100];
    int age;
    char gender[20];
    char contactInformation[100];
    char medical_history[255];
    int assignedDoctorIndex;
    char bloodType[10];
    bool hasInsurance;
} Patient;

typedef struct {
    int patientIndex;
    int doctorIndex;
    int day, month, year;
    float consultationFee;
    float treatmentFee;
    float totalBill;
} Appointment;

typedef struct {
    double total;
    int year;
} Bill;

Doctor* doctors;
int doctor_count;
Patient* patients;
int patient_count;
Appointment *appointments;
int appointment_count;
Bill *bills;
int billsCount;

void addDoctor();
int createPatient();
void addPatient();
void scheduleAppointment();
void deleteDoctor();
void deletePatient();
void updateAppointmentDate();
void deleteAppointment();
void displayDoctors();
void displayPatients();
void displayAppointments();
void saveData();
void loadData();
void hIncome();
void editDoctor();
void editBill();
void editPatient();

#endif //HOSPITALMANAGEMENT_HOSPITALFUNCS_H
