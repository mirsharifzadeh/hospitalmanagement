#include "hospitalfuncs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Doctor *doctors = NULL;
int doctor_count = 0;
Patient *patients = NULL;
int patient_count = 0;
Appointment *appointments = NULL;
int appointment_count = 0;
Bill *bills = NULL;
int billsCount = 0;

const char *SPECIALISATIONS[] = {
    "Cardiology", "Neurology", "Pediatrics", "Orthopedics",
    "Surgery", "Dermatology", "Endocrinology", "Ophthalmology",
    "Gastroenterology", "Hematology", "Oncology",
    "Pulmonology", "Gynecology", "Urology", "Psychiatrist"
};
const int specs = sizeof(SPECIALISATIONS) / sizeof(char*);

const char *BLOOD_TYPES[] = {
    "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
};
const int bloods = sizeof(BLOOD_TYPES) / sizeof(char*);

const char *genders[] = {
    "Male", "Female", "Non-binary"
};

const int gends = sizeof(genders) / sizeof(char*);

int isOnlyLetters(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' ')) {
            return 0;
        }
    }
    return 1;
}

void saveData() {
    FILE *fp = fopen("hospital_data.bin", "wb");
    if (fp == NULL) {
        return;
    }

    fwrite(&doctor_count, sizeof(int), 1, fp);
    if (doctor_count > 0) {
        fwrite(doctors, sizeof(Doctor), doctor_count, fp);
    }

    fwrite(&patient_count, sizeof(int), 1, fp);
    if (patient_count > 0) {
        fwrite(patients, sizeof(Patient), patient_count, fp);
    }

    fwrite(&appointment_count, sizeof(int), 1, fp);
    if (appointment_count > 0) {
        fwrite(appointments, sizeof(Appointment), appointment_count, fp);
    }

    fwrite(&billsCount, sizeof(int), 1, fp);
    if (billsCount > 0) {
        fwrite(bills, sizeof(Bill), billsCount, fp);
    }

    fclose(fp);
}

void loadData() {
    FILE *fp = fopen("hospital_data.bin", "rb");
    if (fp == NULL) {
        return;
    }

    if (fread(&doctor_count, sizeof(int), 1, fp) == 1 && doctor_count > 0) {
        doctors = (Doctor *)malloc(sizeof(Doctor) * doctor_count);
        if (doctors != NULL) {
            fread(doctors, sizeof(Doctor), doctor_count, fp);
        }
    }

    if (fread(&patient_count, sizeof(int), 1, fp) == 1 && patient_count > 0) {
        patients = (Patient *)malloc(sizeof(Patient) * patient_count);
        if (patients != NULL) {
            fread(patients, sizeof(Patient), patient_count, fp);
        }
    }

    if (fread(&appointment_count, sizeof(int), 1, fp) == 1 && appointment_count > 0) {
        appointments = (Appointment *)malloc(sizeof(Appointment) * appointment_count);
        if (appointments != NULL) {
            fread(appointments, sizeof(Appointment), appointment_count, fp);
        }
    }

    if (fread(&billsCount, sizeof(int), 1, fp) == 1 && billsCount > 0) {
        bills = (Bill *)malloc(sizeof(Bill) * billsCount);
        if (bills != NULL) {
            fread(bills, sizeof(Bill), billsCount, fp);
        }
    }

    fclose(fp);
}

void addDoctor() {
    Doctor *temp = realloc(doctors, sizeof(Doctor) * (doctor_count + 1));
    if (temp == NULL) {
        return;
    }
    doctors = temp;

    printf("\n--- Add New Doctor ---\n");
    while (1) {
        printf("Enter Name: ");
        scanf(" %[^\n]", doctors[doctor_count].name);
        if (strcmp(doctors[doctor_count].name, "-1") == 0) {
            printf("---Cancelled---\n");
            temp = realloc(doctors, sizeof(Doctor) * doctor_count);
            if (temp == NULL && doctor_count > 0) {
                return;
            }
            doctors = temp;
            return;
        }
        if (isOnlyLetters(doctors[doctor_count].name)) {
            break;
        }
        printf("Error: Name must contain only letters!\n");
    }

    printf("Select Specialisation:\n");
    for (int i = 0; i < specs; i++) {
        printf("%d. %s\n", i, SPECIALISATIONS[i]);
    }
    int sChoice;
    printf("Choice index: ");
    while (scanf("%d", &sChoice) != 1) {
        scanf("%*s");
        printf("Error: Please enter a number!\nChoice index: ");
    }

    if (sChoice == -1) {
        temp = realloc(doctors, sizeof(Doctor) * doctor_count);
        if (temp == NULL && doctor_count > 0) {
            return;
        }
        doctors = temp;
        printf("---Cancelled---\n");
        return;
    }

    if (sChoice >= 0 && sChoice < specs) {
        strcpy(doctors[doctor_count].specialisation, SPECIALISATIONS[sChoice]);
    } else {
        strcpy(doctors[doctor_count].specialisation, "Undefined");
    }

    printf("Enter Contact Info: ");
    scanf(" %[^\n]", doctors[doctor_count].contactInformation);
    if (strcmp(doctors[doctor_count].contactInformation, "-1") == 0) {
        printf("---Cancelled---\n");
        temp = realloc(doctors, sizeof(Doctor) * doctor_count);
        if (temp == NULL && doctor_count > 0) {
            return;
        }
        doctors = temp;
        return;
    }
    doctors[doctor_count].availability = true;
    doctor_count++;
    printf("Doctor Added Successfully!\n");
    saveData();
}

int createPatient() {
    Patient *temp = realloc(patients, sizeof(Patient) * (patient_count + 1));
    if (temp == NULL) {
        return -1;
    }
    patients = temp;

    printf("\n--- New Patient Registration ---\n");
    while (1) {
        printf("Enter Name: ");
        scanf(" %[^\n]", patients[patient_count].name);
        if (strcmp(patients[patient_count].name, "-1") == 0) {
            printf("---Cancelled---");
            temp = realloc(patients, sizeof(Patient) * patient_count);
            if (temp == NULL && patient_count > 0) {
                return -1;
            }
            patients = temp;
            return -1;
        }
        if (isOnlyLetters(patients[patient_count].name)) {
            break;
        }
        printf("Error: Name must contain only letters!\n");
    }

    printf("Enter Age: ");
    while (scanf("%d", &patients[patient_count].age) != 1) {
        if (patients[patient_count].age == -1) {
            printf("---Cancelled---\n");
            return -1;
        }
        scanf("%*s");
        printf("Error: Please enter age as a number!\nEnter Age: ");
    }


    for (int i = 0; i < gends; i++) {
        printf("%d. %s\n", i, genders[i]);
    }
    int gChoice;

    printf("Select Gender: ");
    scanf("%d", &gChoice);

    while (scanf("%d", &gChoice) != 1) {
        if (gChoice == -1) {
            printf("---Cancelled---\n");
            return -1;
        }
        scanf("%*s");
        printf("Error: Please enter a number!\nSelect Gender: ");
    }

    if (gChoice >= 0 && gChoice < gends) {
        strcpy(patients[patient_count].gender, genders[gChoice]);
    } else {
        strcpy(patients[patient_count].gender, "Undefined");
    }

    printf("Select Blood Type:\n");
    for (int i = 0; i < bloods; i++) {
        printf("%d. %s\n", i, BLOOD_TYPES[i]);
    }
    int bChoice;
    printf("Choice index: ");
    while (scanf("%d", &bChoice) != 1) {
        if (bChoice == -1) {
            printf("---Cancelled---\n");
            return -1;
        }
        scanf("%*s");
        printf("Error: Please enter a number!\nChoice index: ");
    }

    if (bChoice >= 0 && bChoice < bloods) {
        strcpy(patients[patient_count].bloodType, BLOOD_TYPES[bChoice]);
    } else {
        strcpy(patients[patient_count].bloodType, "Unknown");
    }

    printf("Enter Contact Info: ");
    scanf(" %[^\n]", patients[patient_count].contactInformation);
    if (strcmp(patients[patient_count].contactInformation, "-1") == 0) {
        printf("---Cancelled---\n");
        return -1;
    }
    printf("Enter Medical History: ");
    scanf(" %[^\n]", patients[patient_count].medical_history);
    if (strcmp(patients[patient_count].medical_history, "-1") == 0) {
        printf("---Cancelled---\n");
        return -1;
    }

    int insChoice;
    printf("Has Insurance? (1 for Yes, 0 for No): ");
    while (scanf("%d", &insChoice) != 1) {
        if (insChoice == -1) {
            printf("---Cancelled---");
            return -1;
        }
        scanf("%*s");
        printf("Error: Please enter 1 or 0!\nHas Insurance? (1 for Yes, 0 for No): ");
    }
    patients[patient_count].hasInsurance = (insChoice == 1);

    int newIdx = patient_count;
    patient_count++;
    saveData();
    return newIdx;
}

void addPatient() {
    if (createPatient() != -1) {
        printf("Patient added successfully!\n");
    } else {
        printf("---Cancelled---\n");
    }
}

void displayDoctors() {
    printf("\n--- All Doctors ---\n");
    for (int i = 0; i < doctor_count; i++) {
        printf("%d. Dr. %s [%s], Contact: %s, Availability: %s\n", i, doctors[i].name, doctors[i].specialisation, doctors[i].contactInformation, (doctors[i].availability == false) ? "Not Available" : "Available");
    }
}

void displayPatients() {
    if (patient_count == 0) {
        printf("ERROR: No Patients\n");
        return;
    }
    int idx;
    int mh;
    printf("\n--- All Patients ---\n");
    for (int i = 0; i < patient_count; i++) {
        printf("%d. %s (Age: %d) | Gender: %s | Blood: %s | Insurance: %s\n", i, patients[i].name, patients[i].age,
            patients[i].gender, patients[i].bloodType, patients[i].hasInsurance ? "Yes" : "No\n");
    }

    printf("CHECK MEDICAL HISTORY (1 to check) --- ");
    if (scanf(" %d", &mh) != 1) {
        scanf("%*s");
    } else if (mh == 1) {
        printf("Enter the index of the patient that you want to check medical history: ");
        if (scanf("%d", &idx) != 1) {
            scanf("%*s");
            printf("Error: Invalid input!\n");
        } else if (idx < 0 || idx >= patient_count) {
            printf("Error: Patient index out of range!\n");
        } else {
            printf("%s\n", patients[idx].medical_history);
        }
    }
}

void displayAppointments() {
    printf("\n--- All Appointments & Billing ---\n");
    if (appointment_count == 0) {
        printf("No Appointments");
    } else {
        for (int i = 0; i < appointment_count; i++) {
            printf("%d. Date: %02d/%02d/%d | Patient: %s | Doctor: Dr. %s | Total: %.2f AZN\n",
                   i, appointments[i].day, appointments[i].month, appointments[i].year,
                   patients[appointments[i].patientIndex].name,
                   doctors[appointments[i].doctorIndex].name,
                   appointments[i].totalBill);
        }
    }
}

void deleteAppointmentM(int idx) {
    if (idx < 0 || idx >= appointment_count) {
        return;
    }

    for (int i = idx; i < appointment_count - 1; i++) {
        appointments[i] = appointments[i+1];
    }
    appointment_count--;

    if (appointment_count > 0) {
        Appointment *temp = realloc(appointments, sizeof(Appointment) * appointment_count);

        if (temp != NULL) {
            appointments = temp;
        }
    } else {
        free(appointments);
        appointments = NULL;
    }
}

void scheduleAppointment() {
    if (doctor_count == 0) {
        printf("ERROR: No Doctors!\n");
        return;
    }

    displayPatients();
    printf("-2. Create new patient\nSelect Patient Index: ");
    int pIdx;
    while (scanf("%d", &pIdx) != 1) {
        scanf("%*s");
        printf("Error: Please enter a number!\nSelect Patient Index: ");
    }

    if (pIdx == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (pIdx == -2) {
        pIdx = createPatient();
        if (pIdx == -1) return;
    }

    if (pIdx < 0 || pIdx >= patient_count) {
        printf("Error: Patient index out of range!\n");
        return;
    }

    displayDoctors();
    int dIdx;
    printf("Select Doctor Index: ");
    while (scanf("%d", &dIdx) != 1) {
        scanf("%*s");
        printf("Error: Please enter a number!\nSelect Doctor Index: ");
    }

    if (dIdx == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (dIdx < 0 || dIdx >= doctor_count) {
        printf("Error: Doctor index out of range!\n");
        return;
    }

    int d, m, y;
    printf("Enter Date (DD MM YYYY): ");
    while (scanf("%d %d %d", &d, &m, &y) != 3) {
        if (d == -1 || m == -1 || y == -1) {
            printf("---Cancelled---\n");
            return;
        }
        scanf("%*s");
        printf("Error: Please enter the date using numbers (DD MM YYYY): ");
    }

    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].doctorIndex == dIdx &&
            appointments[i].day == d &&
            appointments[i].month == m &&
            appointments[i].year == y) {
            printf("Error: Doctor Dr. %s is already booked on this date!\n", doctors[dIdx].name);
            return;
        }
    }

    Appointment *temp = realloc(appointments, sizeof(Appointment) * (appointment_count + 1));
    Bill *temp2 = realloc(bills, sizeof(Bill) * (billsCount + 1));
    if (temp == NULL || temp2 == NULL) {
        return;
    }
    appointments = temp;
    bills = temp2;

    appointments[appointment_count].day = d;
    appointments[appointment_count].month = m;
    appointments[appointment_count].year = y;
    bills[billsCount].year = y;
    appointments[appointment_count].patientIndex = pIdx;
    appointments[appointment_count].doctorIndex = dIdx;

    printf("Enter Consultation Fee: ");
    while (scanf("%f", &appointments[appointment_count].consultationFee) != 1) {
        if (appointments[appointment_count].consultationFee == -1) {
            printf("---Cancelled---\n");
            return;
        }
        scanf("%*s");
        printf("Error: Please enter the amount as a number!\nEnter Consultation Fee: ");
    }
    printf("Enter Treatment Fee: ");
    while (scanf("%f", &appointments[appointment_count].treatmentFee) != 1) {
        scanf("%*s");
        printf("Error: Please enter the amount as a number!\nEnter Treatment Fee: ");
    }

    if (patients[pIdx].hasInsurance) {
        printf("Patient has insurance. Billing cancelled.\n");
        appointments[appointment_count].totalBill = 0;
        Bill *temp3 = realloc(bills, sizeof(Bill) * (billsCount - 1));
        if (temp3 != NULL) {
            bills = temp3;
        } else {
            return;
        }
    } else {
        appointments[appointment_count].totalBill = appointments[appointment_count].consultationFee + appointments[appointment_count].treatmentFee;
        bills[billsCount].total = appointments[appointment_count].totalBill;
        billsCount++;
        printf("Total Bill: %.2f AZN\n", appointments[appointment_count].totalBill);
    }

    appointment_count++;
    saveData();
    printf("Appointment scheduled successfully!\n");
}

void deleteDoctor() {
    if (doctor_count == 0) {
        printf("Error: No Doctors");
        return;
    }
    displayDoctors();
    int idx;
    printf("Select Doctor: ");
    while (scanf("%d", &idx) != 1) {
        scanf("%*s");
        printf("Error: Please enter a number!\nSelect Doctor: ");
    }

    if (idx == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (idx < 0 || idx >= doctor_count) {
        printf("Error: Doctor index out of range!\n");
        return;
    }

    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].doctorIndex == idx) {
            deleteAppointmentM(i);
            i--;
        } else if (appointments[i].doctorIndex > idx) {
            appointments[i].doctorIndex--;
        }
    }

    for (int i = idx; i < doctor_count - 1; i++) {
        doctors[i] = doctors[i + 1];
    }
    doctor_count--;

    if (doctor_count > 0) {
        Doctor *temp = realloc(doctors, sizeof(Doctor) * doctor_count);
        if (temp != NULL) {
            doctors = temp;
        }
    } else {
        free(doctors);
        doctors = NULL;
    }
    printf("Doctor Deleted Successfully!\n");
    saveData();
}

void deletePatient() {
    if (patient_count == 0) {
        return;
    }
    displayPatients();
    int idx;
    printf("Delete patient index: ");
    while (scanf("%d", &idx) != 1) {
        scanf("%*s");
        printf("Error: Please enter a number!\nDelete patient index: ");
    }

    if (idx == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (idx < 0 || idx >= patient_count) {
        printf("Error: Patient index out of range!\n");
        return;
    }

    for (int i = 0; i < appointment_count; i++) {
        if (appointments[i].patientIndex == idx) {
            deleteAppointmentM(i);
            i--;
        } else if (appointments[i].patientIndex > idx) {
            appointments[i].patientIndex--;
        }
    }

    for (int i = idx; i < patient_count - 1; i++) {
        patients[i] = patients[i + 1];
    }
    patient_count--;

    if (patient_count > 0) {
        Patient *temp = realloc(patients, sizeof(Patient) * patient_count);
        if (temp != NULL) {
            patients = temp;
        }
    } else {
        free(patients);
        patients = NULL;
    }
    printf("Patient Deleted Successfully!\n");
    saveData();
}

void updateAppointmentDate() {
    if (appointment_count == 0) {
        printf("There is no appointments :(");
        return;
    }
    int idx;
    printf("Enter index to reschedule: ");
    while (scanf("%d", &idx) != 1) {
        scanf("%*s");
        printf("Error: Please enter a number!\nEnter index to reschedule: ");
    }

    if (idx == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (idx < 0 || idx >= appointment_count) {
        printf("Error: Appointment index out of range!\n");
        return;
    }

    int d, m, y;
    printf("Enter New Date (DD MM YYYY): ");
    while (scanf("%d %d %d", &d, &m, &y) != 3) {
        scanf("%*s");
        printf("Error: Please enter the date using numbers (DD MM YYYY): ");
    }

    for (int i = 0; i < appointment_count; i++) {
        if (i != idx && appointments[i].doctorIndex == appointments[idx].doctorIndex &&
            appointments[i].day == d && appointments[i].month == m && appointments[i].year == y) {
            printf("Error: Doctor is already busy on that date!\n");
            return;
        }
    }

    appointments[idx].day = d;
    appointments[idx].month = m;
    appointments[idx].year = y;
    printf("Appointment Updated Successfully!\n");
    saveData();
}

void deleteAppointment() {
    if (appointment_count == 0) {
        return;
    }
    displayAppointments();
    int idx;
    printf("Enter index to cancel: ");
    while (scanf("%d", &idx) != 1) {
        scanf("%*s");
        printf("Error: Please enter a number!\nEnter index to cancel: ");
    }

    if (idx == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (idx < 0 || idx >= appointment_count) {
        printf("Error: Appointment index out of range!\n");
        return;
    }

    deleteAppointmentM(idx);
    saveData();
}

void hIncome() {
    if (billsCount <= 0) {
        printf("ERROR: No Bills\n");
        return;
    }

    int *years = malloc(sizeof(int) * billsCount);
    int unique_years_count = 0;

    for (int i = 0; i < billsCount; i++) {
        int isUnique = 1;
        for (int j = 0; j < unique_years_count; j++) {
            if (years[j] == bills[i].year) {
                isUnique = 0;
                break;
            }
        }
        if (isUnique == 1) {
            years[unique_years_count++] = bills[i].year;
        }
    }

    for (int i = 0; i < unique_years_count - 1; i++) {
        for (int j = 0; j < unique_years_count - i - 1; j++) {
            if (years[j] > years[j+1]) {
                int temp = years[j+1];
                years[j+1] = years[j];
                years[j] = temp;
            }
        }
    }

    for (int i = 0; i < unique_years_count; i++) {
        double yearTotal = 0;
        for (int j = 0; j < billsCount; j++) {
            if (bills[j].year == years[i]) {
                yearTotal += bills[j].total;
            }
        }
        printf("Income in %d: %.2lf AZN\n", years[i], yearTotal);
    }
    free(years);
}

void editDoctor() {
    if (doctor_count == 0) {
        printf("Error: No Doctors\n");
        return;
    }
    displayDoctors();
    int dIndex;
    printf("Select Doctor: ");
    while (scanf("%d", &dIndex) != 1) {
        scanf("%*s");
        printf("Error: Index must be a number\nSelect Doctor: ");
    }

    if (dIndex == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (dIndex < 0 || dIndex >= doctor_count) {
        printf("Error: Doctor index out of range!\n");
        return;
    }

    int ne;
    printf("Edit Name (1 to edit) --- ");
    if (scanf("%d", &ne) != 1) {
        scanf("%*s");
        ne = 0;
    }

    if (ne == -1) {
        printf("---Cancelled---");
        return;
    }

    if (ne == 1) {
        while (1) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", doctors[dIndex].name);
            if (strcmp(doctors[dIndex].name, "-1") == 0) {
                printf("---Cancelled---\n");
                return;
            }
            if (isOnlyLetters(doctors[dIndex].name)) {
                break;
            }
            printf("Error: Name must contain only letters!\n");
        }
    }

    int spece;
    printf("Edit Specialization (1 to edit) --- ");
    if (scanf("%d", &spece) != 1) {
        scanf("%*s");
        spece = 0;
    }

    if (spece == 1) {
        printf("Select New Specialisation:\n");
        for (int i = 0; i < specs; i++) {
            printf("%d. %s\n", i, SPECIALISATIONS[i]);
        }
        int sChoice;
        printf("Choice index: ");
        while (scanf("%d", &sChoice) != 1) {
            scanf("%*s");
            printf("Error: Please enter a number!\nChoice index: ");
        }

        if (sChoice == -1) {
            printf("---Cancelled---\n");
            return;
        }

        if (sChoice >= 0 && sChoice < specs) {
            strcpy(doctors[dIndex].specialisation, SPECIALISATIONS[sChoice]);
        } else {
            strcpy(doctors[dIndex].specialisation, "Undefined");
        }
    }

    int cie;
    printf("Edit Contact Information (1 to edit) --- ");
    if (scanf("%d", &cie) != 1) {
        scanf("%*s");
        cie = 0;
    }

    if (cie == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (cie == 1) {
        printf("Enter New Contact Info: ");
        scanf(" %[^\n]", doctors[dIndex].contactInformation);
        if (strcmp(doctors[dIndex].contactInformation, "-1") == 0) {
            printf("---Cancelled---\n");
            return;
        }
    }

    int ae;
    printf("Edit Availability (1 to edit) --- ");
    if (scanf("%d", &ae) != 1) {
        scanf("%*s");
        ae = 0;
    }

    if (ae == 1) {
        int aChoice;
        printf("Select New Avaiability:\n 0. Not Available\n 1. Available\n");
        if (scanf("%d", &aChoice) == 1) {
            if (aChoice == 0) {
                doctors[dIndex].availability = false;
            } else if (aChoice == 1) {
                doctors[dIndex].availability = true;
            } else {
                printf("---Cancelled---\n");
            }
        }
    }

    saveData();
    printf("Doctor Updated Successfully\n");
}

void editPatient() {
    if (patient_count == 0) {
        printf("Error: No Patients\n");
        return;
    }
    displayPatients();
    int pIndex;
    printf("Select Patient Index: ");
    while (scanf("%d", &pIndex) != 1) {
        scanf("%*s");
        printf("Error: Index must be a number\nSelect Patient Index: ");
    }

    if (pIndex == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (pIndex < 0 || pIndex >= patient_count) {
        printf("Error: Patient index out of range!\n");
        return;
    }

    int ne;
    printf("Edit Name (1 to edit) --- ");
    if (scanf("%d", &ne) != 1) {
        scanf("%*s");
        ne = 0;
    }

    if (ne == 1) {
        while (1) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", patients[pIndex].name);
            if (strcmp(patients[pIndex].name, "-1") == 0) {
                printf("---Cancelled---\n");
                return;
            }
            if (isOnlyLetters(patients[pIndex].name)) {
                break;
            }
            printf("Error: Name must contain only letters!\n");
        }
    }

    int ae;
    printf("Edit Age (1 to edit) --- ");
    if (scanf("%d", &ae) != 1) {
        scanf("%*s");
        ae = 0;
    }

    if (ae == 1) {
        printf("Enter New Age: ");
        while (scanf("%d", &patients[pIndex].age) != 1) {
            scanf("%*s");
            printf("Error: Please enter age as a number!\nEnter New Age: ");
        }
    }

    int ge;
    printf("Edit Gender (1 to edit) --- ");
    if (scanf("%d", &ge) != 1) {
        scanf("%*s");
        ge = 0;
    }

    if (ge == 1) {
        for (int i = 0; i < gends; i++) {
            printf("%d. %s\n", i, genders[i]);
        }
        int gChoice;
        printf("Select New Gender: ");
        if (scanf("%d", &gChoice) == 1) {
            if (gChoice >= 0 && gChoice < gends) {
                strcpy(patients[pIndex].gender, genders[gChoice]);
            }
        }
    }

    int be;
    printf("Edit Blood Type (1 to edit) --- ");
    if (scanf("%d", &be) != 1) {
        scanf("%*s");
        be = 0;
    }

    if (be == 1) {
        for (int i = 0; i < bloods; i++) {
            printf("%d. %s\n", i, BLOOD_TYPES[i]);
        }
        int bChoice;
        printf("Choice index: ");
        if (scanf("%d", &bChoice) == 1) {
            if (bChoice >= 0 && bChoice < bloods) {
                strcpy(patients[pIndex].bloodType, BLOOD_TYPES[bChoice]);
            }
        }
    }

    int cie;
    printf("Edit Contact Information (1 to edit) --- ");
    if (scanf("%d", &cie) != 1) {
        scanf("%*s");
        cie = 0;
    }

    if (cie == 1) {
        printf("Enter New Contact Info: ");
        scanf(" %[^\n]", patients[pIndex].contactInformation);
    }

    int mhe;
    printf("Edit Medical History (1 to edit) --- ");
    if (scanf("%d", &mhe) != 1) {
        scanf("%*s");
        mhe = 0;
    }

    if (mhe == 1) {
        printf("Enter New Medical History: ");
        scanf(" %[^\n]", patients[pIndex].medical_history);
    }

    int inse;
    printf("Edit Insurance Status (1 to edit) --- ");
    if (scanf("%d", &inse) != 1) {
        scanf("%*s");
        inse = 0;
    }

    if (inse == 1) {
        int insChoice;
        printf("Has Insurance? (1 for Yes, 0 for No): ");
        if (scanf("%d", &insChoice) == 1) {
            patients[pIndex].hasInsurance = (insChoice == 1);
        }
    }

    saveData();
    printf("Patient Updated Successfully!\n");
}

void editBill() {
    if (billsCount == 0) {
        printf("Error: No Bills found\n");
        return;
    }

    printf("\n--- All Bills ---\n");
    for (int i = 0; i < billsCount; i++) {
        printf("%d. Year: %d | Total: %.2f AZN\n", i, bills[i].year, bills[i].total);
    }

    int bIndex;
    printf("Select Bill Index: ");
    while (scanf("%d", &bIndex) != 1) {
        scanf("%*s");
        printf("Error: Index must be a number\nSelect Bill Index: ");
    }

    if (bIndex == -1) {
        printf("---Cancelled---\n");
        return;
    }

    if (bIndex < 0 || bIndex >= billsCount) {
        printf("Error: Bill index out of range!\n");
        return;
    }

    int ye;
    printf("Edit Year (1 to edit) --- ");
    if (scanf("%d", &ye) != 1) {
        scanf("%*s");
        ye = 0;
    }

    if (ye == 1) {
        printf("Enter New Year: ");
        while (scanf("%d", &bills[bIndex].year) != 1) {
            scanf("%*s");
            printf("Error: Year must be a number!\nEnter New Year: ");
        }
    }

    int te;
    printf("Edit Total Amount (1 to edit) --- ");
    if (scanf("%d", &te) != 1) {
        scanf("%*s");
        te = 0;
    }

    if (te == 1) {
        printf("Enter New Total Amount: ");
        while (scanf("%f", &bills[bIndex].total) != 1) {
            scanf("%*s");
            printf("Error: Amount must be a number!\nEnter New Total: ");
        }
    }

    saveData();
    printf("Bill Updated Successfully!\n");
}