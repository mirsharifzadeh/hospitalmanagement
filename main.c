#include <stdio.h>
#include <stdlib.h>
#include "hospitalfuncs.c"

int main() {
    loadData();
    int choice;
    while (1) {
        printf("\n--- Hospital Management & Billing System ---\n");
        printf("1. Add Doctor\t\t2. Add Patient\n");
        printf("3. Schedule Appointment\t4. Display All Doctors\n");
        printf("5. Display All Patients\t6. Display Appointments & Bills\n");
        printf("7. Delete Doctor\t8. Delete Patient\n");
        printf("9. Reschedule Appt.\t10. Delete Appointment\n");
        printf("11. Display Annual Income\n");
        printf("12. Edit Doctors  13. Edit Patient  14.Edit Bills\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0: {
                free(doctors);
                free(patients);
                free(appointments);
                free(bills);
                return 0;
            }
            case 1: {
                addDoctor();
                break;
            }
            case 2: {
                addPatient();
                break;
            }
            case 3: {
                scheduleAppointment();
                break;
            }
            case 4: {
                displayDoctors();
                break;
            }
            case 5: {
                displayPatients();
                break;
            }
            case 6: {
                displayAppointments();
                break;
            }
            case 7: {
                deleteDoctor();
                break;
            }
            case 8: {
                deletePatient();
                break;
            }
            case 9: {
                updateAppointmentDate();
                break;
            }
            case 10: {
                deleteAppointment();
                break;
            }
            case 11: {
                hIncome();
                break;
            }
            case 12: {
                editDoctor();
                break;
            }
            case 13: {
                editPatient();
                break;
            }
            case 14: {
                editBill();
                break;
            }
            default: {
                printf("Invalid choice!\n");
            }
        }
    }
}