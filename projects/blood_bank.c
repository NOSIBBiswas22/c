#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Donor {
    int id;
    char name[50];
    int age;
    char blood[5];
    char phone[15];
    int donations;
    struct Donor *next;
};

struct History {
    int donorId;
    char name[50];
    char blood[5];
    int units;
    struct History *next;
};

struct Request {
    int id;
    char patient[50];
    char blood[5];
    int units;
    char hospital[50];
    struct Request *next;
};

struct Donor *donorHead = NULL;
struct History *historyTop = NULL;
struct Request *reqFront = NULL;
struct Request *reqRear = NULL;

int nextDonorId = 1;
int nextRequestId = 1;

char bloodGroups[8][5] = {"A+","A-","B+","B-","AB+","AB-","O+","O-"};
int  bloodStock[8] = {0,0,0,0,0,0,0,0};

void line() {
    printf("------------------------------------------\n");
}

int bloodIndex(char *bg) {
    int i;
    for (i = 0; i < 8; i++)
        if (strcmp(bloodGroups[i], bg) == 0) return i;
    return -1;
}

void addDonor() {
    struct Donor *d = (struct Donor *)malloc(sizeof(struct Donor));
    d->id = nextDonorId++;
    d->donations = 0;
    d->next = NULL;

    printf("\n--- ADD DONOR ---\n");
    printf("Name  : "); scanf(" %49[^\n]", d->name);
    printf("Age   : "); scanf(" %d", &d->age);
    printf("Blood Group (e.g. A+, B-, O+): "); scanf(" %4s", d->blood);
    printf("Phone : "); scanf(" %14s", d->phone);

    if (donorHead == NULL) {
        donorHead = d;
    } else {
        struct Donor *cur = donorHead;
        while (cur->next != NULL) cur = cur->next;
        cur->next = d;
    }

    int idx = bloodIndex(d->blood);
    if (idx >= 0) bloodStock[idx]++;

    printf("\nDonor added! ID = %d\n", d->id);
}

void viewDonors() {
    if (donorHead == NULL) {
        printf("\nNo donors found.\n");
        return;
    }
    printf("\n--- ALL DONORS ---\n");
    line();
    printf("%-4s %-20s %-4s %-5s %-12s %-7s\n",
           "ID", "Name", "Age", "Blood", "Phone", "Donated");
    line();
    struct Donor *cur = donorHead;
    while (cur != NULL) {
        printf("%-4d %-20s %-4d %-5s %-12s %-7d\n",
               cur->id, cur->name, cur->age,
               cur->blood, cur->phone, cur->donations);
        cur = cur->next;
    }
    line();
}

void searchDonor() {
    char bg[5];
    printf("\nEnter Blood Group to search: ");
    scanf(" %4s", bg);

    int found = 0;
    struct Donor *cur = donorHead;
    printf("\nDonors with blood group %s:\n", bg);
    line();
    while (cur != NULL) {
        if (strcmp(cur->blood, bg) == 0) {
            printf("ID: %d | Name: %s | Phone: %s\n",
                   cur->id, cur->name, cur->phone);
            found = 1;
        }
        cur = cur->next;
    }
    if (!found) printf("No donors found for blood group %s.\n", bg);
    line();
}

void deleteDonor() {
    int id;
    printf("\nEnter Donor ID to delete: ");
    scanf(" %d", &id);

    struct Donor *cur = donorHead, *prev = NULL;
    while (cur != NULL) {
        if (cur->id == id) {
            if (prev == NULL) donorHead = cur->next;
            else prev->next = cur->next;
            int idx = bloodIndex(cur->blood);
            if (idx >= 0 && bloodStock[idx] > 0) bloodStock[idx]--;
            free(cur);
            printf("Donor deleted.\n");
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    printf("Donor ID %d not found.\n", id);
}

void pushHistory(int donorId, char *name, char *blood, int units) {
    struct History *h = (struct History *)malloc(sizeof(struct History));
    h->donorId = donorId;
    strcpy(h->name, name);
    strcpy(h->blood, blood);
    h->units = units;
    h->next = historyTop;
    historyTop = h;
}

void viewHistory() {
    if (historyTop == NULL) {
        printf("\nNo donation history.\n");
        return;
    }
    printf("\n--- DONATION HISTORY (latest first) ---\n");
    line();
    printf("%-8s %-20s %-5s %-5s\n", "DonorID", "Name", "Blood", "Units");
    line();
    struct History *h = historyTop;
    while (h != NULL) {
        printf("%-8d %-20s %-5s %-5d\n",
               h->donorId, h->name, h->blood, h->units);
        h = h->next;
    }
    line();
}

void recordDonation() {
    int id, units;
    printf("\nEnter Donor ID: ");
    scanf(" %d", &id);

    struct Donor *cur = donorHead;
    while (cur != NULL) {
        if (cur->id == id) {
            printf("Units donated: ");
            scanf(" %d", &units);
            cur->donations += units;
            int idx = bloodIndex(cur->blood);
            if (idx >= 0) bloodStock[idx] += units;
            pushHistory(cur->id, cur->name, cur->blood, units);
            printf("Donation recorded. Stock of %s: %d\n",
                   cur->blood, (idx >= 0) ? bloodStock[idx] : 0);
            return;
        }
        cur = cur->next;
    }
    printf("Donor not found.\n");
}

void addRequest() {
    struct Request *r = (struct Request *)malloc(sizeof(struct Request));
    r->id = nextRequestId++;
    r->next = NULL;

    printf("\n--- ADD BLOOD REQUEST ---\n");
    printf("Patient Name : "); scanf(" %49[^\n]", r->patient);
    printf("Blood Group  : "); scanf(" %4s", r->blood);
    printf("Units Needed : "); scanf(" %d", &r->units);
    printf("Hospital     : "); scanf(" %49[^\n]", r->hospital);

    if (reqRear == NULL) {
        reqFront = reqRear = r;
    } else {
        reqRear->next = r;
        reqRear = r;
    }
    printf("\nRequest #%d added to queue.\n", r->id);
}

void viewRequests() {
    if (reqFront == NULL) {
        printf("\nNo pending requests.\n");
        return;
    }
    printf("\n--- PENDING BLOOD REQUESTS ---\n");
    line();
    printf("%-4s %-20s %-5s %-5s %-20s\n",
           "ID", "Patient", "Blood", "Units", "Hospital");
    line();
    struct Request *r = reqFront;
    while (r != NULL) {
        printf("%-4d %-20s %-5s %-5d %-20s\n",
               r->id, r->patient, r->blood, r->units, r->hospital);
        r = r->next;
    }
    line();
}

void fulfillRequest() {
    if (reqFront == NULL) {
        printf("\nNo requests in queue.\n");
        return;
    }
    struct Request *r = reqFront;
    int idx = bloodIndex(r->blood);
    int stock = (idx >= 0) ? bloodStock[idx] : 0;

    printf("\nNext Request:\n");
    printf("Patient  : %s\n", r->patient);
    printf("Blood    : %s\n", r->blood);
    printf("Units    : %d\n", r->units);
    printf("Hospital : %s\n", r->hospital);
    printf("In Stock : %d units\n", stock);

    if (stock < r->units) {
        printf("Not enough stock. Cannot fulfill.\n");
        return;
    }

    char c;
    printf("Fulfill this request? (y/n): ");
    scanf(" %c", &c);
    if (c == 'y' || c == 'Y') {
        bloodStock[idx] -= r->units;
        reqFront = reqFront->next;
        if (reqFront == NULL) reqRear = NULL;
        printf("Request fulfilled! %s stock left: %d\n",
               r->blood, bloodStock[idx]);
        free(r);
    } else {
        printf("Cancelled.\n");
    }
}

void viewInventory() {
    int i;
    printf("\n--- BLOOD INVENTORY ---\n");
    line();
    printf("%-6s %-6s  Status\n", "Group", "Units");
    line();
    for (i = 0; i < 8; i++) {
        char *status;
        if      (bloodStock[i] == 0) status = "EMPTY";
        else if (bloodStock[i] < 5)  status = "Low";
        else                         status = "OK";
        printf("%-6s %-6d  %s\n", bloodGroups[i], bloodStock[i], status);
    }
    line();
}

void saveToFile() {
    int i;
    FILE *f;

    f = fopen("donors.txt", "w");
    if (f != NULL) {
        fprintf(f, "%d\n", nextDonorId);
        struct Donor *d = donorHead;
        while (d != NULL) {
            fprintf(f, "%d|%s|%d|%s|%s|%d\n",
                    d->id, d->name, d->age,
                    d->blood, d->phone, d->donations);
            d = d->next;
        }
        fclose(f);
    }

    f = fopen("requests.txt", "w");
    if (f != NULL) {
        fprintf(f, "%d\n", nextRequestId);
        struct Request *r = reqFront;
        while (r != NULL) {
            fprintf(f, "%d|%s|%s|%d|%s\n",
                    r->id, r->patient, r->blood,
                    r->units, r->hospital);
            r = r->next;
        }
        fclose(f);
    }

    f = fopen("stock.txt", "w");
    if (f != NULL) {
        for (i = 0; i < 8; i++)
            fprintf(f, "%s|%d\n", bloodGroups[i], bloodStock[i]);
        fclose(f);
    }

    printf("Data saved to txt files.\n");
}

void loadFromFile() {
    int i;
    FILE *f;

    f = fopen("donors.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d\n", &nextDonorId);
        char line[200];
        while (fgets(line, sizeof(line), f)) {
            struct Donor *d = (struct Donor *)malloc(sizeof(struct Donor));
            d->next = NULL;
            if (sscanf(line, "%d|%49[^|]|%d|%4[^|]|%14[^|]|%d",
                       &d->id, d->name, &d->age,
                       d->blood, d->phone, &d->donations) == 6) {
                if (donorHead == NULL) donorHead = d;
                else {
                    struct Donor *cur = donorHead;
                    while (cur->next) cur = cur->next;
                    cur->next = d;
                }
            } else free(d);
        }
        fclose(f);
    }

    f = fopen("requests.txt", "r");
    if (f != NULL) {
        fscanf(f, "%d\n", &nextRequestId);
        char line[200];
        while (fgets(line, sizeof(line), f)) {
            struct Request *r = (struct Request *)malloc(sizeof(struct Request));
            r->next = NULL;
            if (sscanf(line, "%d|%49[^|]|%4[^|]|%d|%49[^\n]",
                       &r->id, r->patient, r->blood,
                       &r->units, r->hospital) == 5) {
                if (reqRear == NULL) reqFront = reqRear = r;
                else { reqRear->next = r; reqRear = r; }
            } else free(r);
        }
        fclose(f);
    }

    f = fopen("stock.txt", "r");
    if (f != NULL) {
        char bg[5]; int units;
        while (fscanf(f, "%4[^|]|%d\n", bg, &units) == 2)
            for (i = 0; i < 8; i++)
                if (strcmp(bloodGroups[i], bg) == 0)
                    bloodStock[i] = units;
        fclose(f);
    }
}

void donorMenu() {
    int ch;
    do {
        printf("\n=== DONOR MENU ===\n");
        printf("1. Add Donor\n");
        printf("2. View All Donors\n");
        printf("3. Search by Blood Group\n");
        printf("4. Delete Donor\n");
        printf("5. Record Donation\n");
        printf("6. View Donation History\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf(" %d", &ch);
        switch (ch) {
            case 1: addDonor(); break;
            case 2: viewDonors(); break;
            case 3: searchDonor(); break;
            case 4: deleteDonor(); break;
            case 5: recordDonation(); break;
            case 6: viewHistory(); break;
        }
    } while (ch != 0);
}

void requestMenu() {
    int ch;
    do {
        printf("\n=== REQUEST MENU ===\n");
        printf("1. Add Blood Request\n");
        printf("2. View All Requests\n");
        printf("3. Fulfill Next Request\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf(" %d", &ch);
        switch (ch) {
            case 1: addRequest(); break;
            case 2: viewRequests(); break;
            case 3: fulfillRequest(); break;
        }
    } while (ch != 0);
}

int main() {
    int ch;
    loadFromFile();

    printf("==========================================\n");
    printf("     BLOOD BANK MANAGEMENT SYSTEM\n");
    printf("     Data Structure Course Project\n");
    printf("==========================================\n");

    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Donor Management\n");
        printf("2. Blood Requests\n");
        printf("3. Blood Inventory\n");
        printf("4. Save Data\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf(" %d", &ch);

        switch (ch) {
            case 1: donorMenu(); break;
            case 2: requestMenu(); break;
            case 3: viewInventory(); break;
            case 4: saveToFile(); break;
            case 0:
                saveToFile();
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (ch != 0);

    return 0;
}
