#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void execute_query(const char *query) {
    printf("Executing query: %s\n", query);
}

char **fetch_result(const char *query) {
    printf("Fetching result for query: %s\n", query);
    static char *mock_result[] = {"Mock Name", "2024-01-01", "Mock Father", "Mock Mother", "Mock City", "2024-01-15", NULL};
    return mock_result;
}

void new_case();
void patient_details();
void quarantine_left();
void precautions();
void quarantine_completed();
void postcautions();
void signs_and_symptoms();
void print_colored_text(const char *color, const char *text);
void update_bed_count(int action);

int total_beds = 100;  // Total beds available in the facility
int beds_in_use = 0;   // Number of beds in use

int main() {
    int choice;

    while (1) {
        printf("\n====================== ======================\n");
        printf(" _______    _______              _________   ______           _______    _______    _          _______    _______    _______    _______    _______    _         _________\n");
        printf("(  ____ \\  (  ___  )  |\\     /|  \\__   __/  (  __  \\         (       )  (  ___  )  ( (    /|  (  ___  )  (  ____ \\  (  ____ \\  (       )  (  ____ \\  ( (    /|  \\__   __/\n");
        printf("| (    \\/  | (   ) |  | )   ( |     ) (     | (  \\  )        | () () |  | (   ) |  |  \\  ( |  | (   ) |  | (    \\/  | (    \\/  | () () |  | (    \\/  |  \\  ( |     ) (   \n");
        printf("| |        | |   | |  | |   | |     | |     | |   ) |        | || || |  | (___) |  |   \\ | |  | (___) |  | |        | (__      | || || |  | (__      |   \\ | |     | |   \n");
        printf("| |        | |   | |  ( (   ) )     | |     | |   | |        | |(_)| |  |  ___  |  | (\\ \\) |  |  ___  |  | | ____   |  __)     | |(_)| |  |  __)     | (\\ \\) |     | |   \n");
        printf("| |        | |   | |   \\ \\_/ /      | |     | |   ) |        | |   | |  | (   ) |  | | \\   |  | (   ) |  | | \\_  )  | (        | |   | |  | (        | | \\   |     | |   \n");
        printf("| (____\\/  | (___) |    \\   /    ___) (___  | (__/  )        | )   ( |  | )   ( |  | )  \\  |  | )   ( |  | (___) |  | (____\\/  | )   ( |  | (____\\/  | )  \\  |     | |   \n");
        printf("(_______/  (_______)     \\_/     \\_______/  (______/         |/     \\|  |/     \\|  |/    )_)  |/     \\|  (_______)  (_______/  |/     \\|  (_______/  |/    )_)     )_(    \n");
        printf("=======================================================\n");
        printf("\n=== COVID-19 Quarantine Management System ===\n");
        printf("1. Add a New Case\n");
        printf("2. Get Patient Details\n");
        printf("3. Check Quarantine Days Left\n");
        printf("4. Display COVID-19 Precautions\n");
        printf("5. Show Patients Who Completed Quarantine\n");
        printf("6. Display Post Discharge Caution Measures\n");
        printf("7. Display Signs and Symptoms of COVID-19\n");
        printf("8. View Bed Count\n");
        printf("9. Exit\n");
        printf(">>> Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                new_case();
                break;
            case 2:
                patient_details();
                break;
            case 3:
                quarantine_left();
                break;
            case 4:
                precautions();
                break;
            case 5:
                quarantine_completed();
                break;
            case 6:
                postcautions();
                break;
            case 7:
                signs_and_symptoms();
                break;
            case 8:
                printf("Total beds: %d\n", total_beds);
                printf("Beds in use: %d\n", beds_in_use);
                printf("Beds available: %d\n", total_beds - beds_in_use);
                break;
            case 9:
                printf("Exiting the program. Stay safe!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void new_case() {
    int case_id;
    char name[100], doa[15], f_name[100], m_name[100], city[100], bed[10];
    char query[1024];

    printf(">>> Enter case id for the Patient --> ");
    scanf("%d", &case_id);
    printf(">>> Enter name of the Patient --> ");
    scanf("%s", name);
    printf(">>> Please specify Date of admitting the patient (YYYY-MM-DD) --> ");
    scanf("%s", doa);

    struct tm tm;
    strptime(doa, "%Y-%m-%d", &tm);
    tm.tm_mday += 14;
    mktime(&tm);
    char dod[15];
    strftime(dod, sizeof(dod), "%Y-%m-%d", &tm);

    printf(">>> Enter Father's name --> ");
    scanf("%s", f_name);
    printf(">>> Enter Mother's name --> ");
    scanf("%s", m_name);
    printf(">>> Enter city of the patient --> ");
    scanf("%s", city);
    printf(">>> Enter bed id of bed allocated --> ");
    scanf("%s", bed);

    if (beds_in_use < total_beds) {
        beds_in_use++;
        sprintf(query, "INSERT INTO cases VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
                case_id, name, doa, f_name, m_name, city, dod, bed);
        execute_query(query);
        printf("++ New case added successfully!\n");
    } else {
        printf("++ No available beds. Please try again later.\n");
    }
}

void patient_details() {
    int case_id;
    char query[512];

    printf(">>> Enter case id for the Patient --> ");
    scanf("%d", &case_id);
    sprintf(query, "SELECT * FROM cases WHERE case_number = %d", case_id);
    char **result = fetch_result(query);

    printf("++ Name of patient with id %d --\t%s\n", case_id, result[0]);
    printf("++ Date of Admitting the patient --\t%s\n", result[1]);
    printf("++ Father's name --\t\t\t%s\n", result[2]);
    printf("++ Mother's name --\t\t\t%s\n", result[3]);
    printf("++ Current city --\t\t\t%s\n", result[4]);
    printf("++ Date of Discharging the patient --\t%s\n", result[5]);
}

void quarantine_left() {
    int case_id;
    char query[512];

    printf(">>> Enter case id for the Patient --> ");
    scanf("%d", &case_id);
    sprintf(query, "SELECT date_of_discharge, patient_name FROM cases WHERE case_number = %d", case_id);
    char **result = fetch_result(query);

    struct tm tm;
    time_t today = time(NULL);
    strptime(result[0], "%Y-%m-%d", &tm);
    time_t discharge_date = mktime(&tm);

    int days_left = (int)difftime(discharge_date, today) / (60 * 60 * 24);
    printf("++ There are %d days left to discharge %s\n", days_left, result[1]);
}

void precautions() {
    printf("\n\"Protect yourself and others around you by taking appropriate precautions.\n"
           "Follow these advices to prevent the spread of COVID-19:\"\n");
    printf("  - Clean your hands often. Use soap and water, or an alcohol-based hand rub.\n");
    printf("  - Maintain a safe distance from anyone coughing or sneezing.\n");
    printf("  - Wear a mask when physical distancing is not possible.\n");
    printf("  - Don’t touch your eyes, nose, or mouth.\n");
    printf("  - Cover your nose and mouth with your elbow or a tissue when you cough or sneeze.\n");
    printf("  - Stay home if you feel unwell.\n");
    printf("  - If you have a fever, cough, and difficulty breathing, seek medical attention.\n");
}

void quarantine_completed() {
    char query[512];
    time_t today = time(NULL);
    struct tm *tm = localtime(&today);
    char today_str[15];
    strftime(today_str, sizeof(today_str), "%Y-%m-%d", tm);

    sprintf(query, "SELECT case_number, patient_name, date_of_discharge FROM cases WHERE date_of_discharge < '%s'", today_str);
    char **result = fetch_result(query);

    printf("++ Quarantine Period of the following Patients is completed:\n");
    while (*result) {
        printf("  - Case ID: %s, Name: %s, Date of Discharge: %s\n", result[0], result[1], result[2]);
        result += 3;
    }
}

void print_colored_text(const char *color, const char *text) {
    printf("%s%s\033[0m", color, text);
}

void postcautions() {
    printf("\n");
    print_colored_text("\033[31m", "\" Now, once someone had recovered from Covid and got Discharged.\n"
                                   "He/she must follow certain measures in order to enjoy a healthy life ahead.\"\n");
    print_colored_text("\033[35m", "\n    +++>  The first follow-up visit (physical/telephonic) should be within 7 days after discharge, preferably at the hospital where he/she underwent treatment.\n");
    print_colored_text("\033[35m", "    +++>  Subsequent treatment/follow up visits may be with the nearest qualified allopathic/AYUSH practitioner/medical facility of other systems of medicine.\n");
    print_colored_text("\033[35m", "    +++>  Poly-therapy is to be avoided due to potential for unknown drug-drug interaction, which may lead to Serious Adverse Events (SAE) or Adverse Effects (AE).\n");
    print_colored_text("\033[35m", "    +++>  The patients who had undergone home isolation, if they complain of persisting symptoms, will visit the nearest health facility.\n");
    print_colored_text("\033[35m", "    +++>  Severe cases requiring critical care support will require more stringent follow up.\n");
}

void signs_and_symptoms() {
    printf("\n");
    print_colored_text("\033[31m", "COVID-19 affects different people in different ways. Most infected people will develop mild to moderate illness and recover without hospitalization.\n");
    print_colored_text("\033[35m", ">>>  Most common symptoms:\n");
    print_colored_text("\033[34m", "              > fever\n              > cough\n              > tiredness\n              > loss of taste or smell\n");
    print_colored_text("\033[35m", ">>>  Less common symptoms:\n");
    print_colored_text("\033[34m", "              > aches and pains\n              > nasal congestion\n              > headache\n              > conjunctivitis\n              > sore throat\n");
    print_colored_text("\033[35m", ">>>  Serious symptoms:\n");
    print_colored_text("\033[34m", "              > difficulty breathing or shortness of breath\n              > chest pain or pressure\n              > loss of speech or movement\n");
}

void update_bed_count(int action) {
    if (action == 1) {
        if (beds_in_use < total_beds) {
            beds_in_use++;
            printf("A bed has been allocated. Beds in use: %d\n", beds_in_use);
        } else {
            printf("Error: No available beds left.\n");
        }
    } else if (action == -1) {
        if (beds_in_use > 0) {
            beds_in_use--;
            printf("A bed has been freed. Beds in use: %d\n", beds_in_use);
        } else {
            printf("Error: No beds in use to free.\n");
        }
    } else {
        printf("Error: Invalid action. Use 1 to allocate a bed or -1 to free a bed.\n");
    }
}
