#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef _WIN32
  #include <windows.h>
  static void sleep_ms(int ms) { Sleep(ms); }
  static void platform_init(void) {
      SetConsoleOutputCP(CP_UTF8);
      HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
      DWORD mode = 0;
      if (GetConsoleMode(h, &mode))
          SetConsoleMode(h, mode | 0x0004); 
  }
#else
  #include <unistd.h>
  static void sleep_ms(int ms) { usleep(ms * 1000); }
  static void platform_init(void) { }
#endif

#define RST   "\x1b[0m"
#define BOLD  "\x1b[1m"
#define DIM   "\x1b[2m"
#define RED   "\x1b[31m"
#define GRN   "\x1b[32m"
#define YEL   "\x1b[33m"
#define BLU   "\x1b[34m"
#define MAG   "\x1b[35m"
#define CYN   "\x1b[36m"
#define WHT   "\x1b[97m"

#define W 56  

#define RATE 25   

typedef struct {
    int  token;
    int  room_num;
    char name[50];
    int  num_clothes;
    char status[24];          
} Laundry;

typedef struct QueueNode {
    Laundry data;
    struct QueueNode *next;
} QueueNode;

typedef struct BSTNode {
    Laundry data;
    struct BSTNode *left, *right;
} BSTNode;

static QueueNode *front = NULL, *rear = NULL;
static BSTNode   *storageRoot = NULL;
static int nextToken = 1001;

static void line(const char *colour, char ch) {
    printf("%s", colour);
    printf("%s", ch == 'T' ? "╔" : ch == 'M' ? "╠" : "╚");
    for (int i = 0; i < W; i++) printf("═");
    printf("%s%s\n", ch == 'T' ? "╗" : ch == 'M' ? "╣" : "╝", RST);
}

static void row(const char *colour, const char *text) {
    printf("%s║%s %-*s %s║%s\n", colour, RST, W - 2, text, colour, RST);
}

static void rowf(const char *colour, const char *fmt, ...) {
    char buf[256];
    va_list ap; va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    row(colour, buf);
}

static void centered(const char *colour, const char *text) {
    int len = (int)strlen(text);
    int pad = (W - 2 - len) / 2;
    char buf[128];
    snprintf(buf, sizeof buf, "%*s%s", pad, "", text);
    row(colour, buf);
}

static void clearScreen(void) { printf("\x1b[2J\x1b[H"); }

static void pause_(void) {
    printf(DIM "\n   press Enter to continue..." RST);
    while (getchar() != '\n');
}

static int readInt(const char *prompt) {
    int v; int c;
    for (;;) {
        printf(CYN "  %s " RST, prompt);
        if (scanf("%d", &v) == 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            return v;
        }
        while ((c = getchar()) != '\n' && c != EOF);
        printf(RED "  ✗ Numbers only, please.\n" RST);
    }
}

static void readLine(const char *prompt, char *dst, size_t n) {
    printf(CYN "  %s " RST, prompt);
    if (fgets(dst, (int)n, stdin)) dst[strcspn(dst, "\n")] = '\0';
    if (dst[0] == '\0') strcpy(dst, "Guest");
}

static void enqueue(Laundry item) {
    QueueNode *n = malloc(sizeof *n);
    if (!n) { printf(RED "Out of memory\n" RST); return; }
    n->data = item; n->next = NULL;
    if (!rear) { front = rear = n; return; }
    rear->next = n; rear = n;
}

static int dequeue(Laundry *out) {
    if (!front) return 0;
    QueueNode *t = front;
    *out = t->data;
    front = t->next;
    if (!front) rear = NULL;
    free(t);
    return 1;
}

static int queueCount(void) {
    int c = 0;
    for (QueueNode *t = front; t; t = t->next) c++;
    return c;
}

static BSTNode *insertBST(BSTNode *root, Laundry item) {
    if (!root) {
        BSTNode *n = malloc(sizeof *n);
        n->data = item; n->left = n->right = NULL;
        return n;
    }
    if (item.room_num < root->data.room_num)      root->left  = insertBST(root->left, item);
    else if (item.room_num > root->data.room_num) root->right = insertBST(root->right, item);
    else root->data = item;
    return root;
}

static BSTNode *searchBST(BSTNode *root, int room) {
    if (!root || root->data.room_num == room) return root;
    return room < root->data.room_num ? searchBST(root->left, room)
                                      : searchBST(root->right, room);
}

static BSTNode *minNode(BSTNode *n) { while (n->left) n = n->left; return n; }

static BSTNode *deleteBST(BSTNode *root, int room) {
    if (!root) return NULL;
    if (room < root->data.room_num)      root->left  = deleteBST(root->left, room);
    else if (room > root->data.room_num) root->right = deleteBST(root->right, room);
    else {
        if (!root->left)  { BSTNode *r = root->right; free(root); return r; }
        if (!root->right) { BSTNode *l = root->left;  free(root); return l; }
        BSTNode *s = minNode(root->right);
        root->data = s->data;
        root->right = deleteBST(root->right, s->data.room_num);
    }
    return root;
}

static void inorderPrint(BSTNode *root, int *count) {
    if (!root) return;
    inorderPrint(root->left, count);
    rowf(GRN, " #%d   Room %-5d %-18.18s %2d pcs",
         root->data.token, root->data.room_num, root->data.name, root->data.num_clothes);
    (*count)++;
    inorderPrint(root->right, count);
}

static void freeBST(BSTNode *root) {
    if (!root) return;
    freeBST(root->left); freeBST(root->right); free(root);
}

static void washAnimation(int clothes) {
    const char *spin[] = { "◐", "◓", "◑", "◒" };
    const char *stage[] = { "Soaking", "Washing", "Rinsing", "Spinning", "Ironing", "Folding" };
    for (int i = 0; i <= 30; i++) {
        int s = i * 6 / 31;
        printf("\r   %s%s%s  %-9s " CYN, MAG, spin[i % 4], RST, stage[s]);
        for (int b = 0; b < 30; b++) printf("%s", b < i ? "█" : " ");
        printf(RST " %3d%%", i * 100 / 30);
        fflush(stdout);
        sleep_ms(55);
    }
    printf("\r   " GRN "✓" RST "  Done      " GRN);
    for (int b = 0; b < 30; b++) printf("█");
    printf(RST " 100%%   " DIM "(%d pieces)" RST "\n", clothes);
}

static void banner(void) {
    line(CYN, 'T');
    centered(CYN, "L A U N D R Y   M A N A G E R");
    centered(CYN, "Queue -> Wash -> BST Storage");
    line(CYN, 'M');
    rowf(CYN, " In queue: %-3d          In storage: %s",
         queueCount(), storageRoot ? "yes" : "empty");
    line(CYN, 'B');
}

static void menu(void) {
    line(BLU, 'T');
    centered(BLU, "M E N U");
    line(BLU, 'M');
    row(BLU, " 1  Take new laundry        (enqueue)");
    row(BLU, " 2  Process next load       (dequeue -> BST)");
    row(BLU, " 3  Check status            (search)");
    row(BLU, " 4  View pending queue");
    row(BLU, " 5  View storage shelf      (in-order)");
    row(BLU, " 6  Deliver to guest        (BST delete)");
    row(BLU, " 0  Exit");
    line(BLU, 'B');
}

static void receiveOrder(void) {
    Laundry o;
    line(YEL, 'T'); centered(YEL, "NEW ORDER"); line(YEL, 'B');
    o.room_num    = readInt("Room number :");
    readLine("Guest name  :", o.name, sizeof o.name);
    o.num_clothes = readInt("Pieces      :");
    if (o.num_clothes < 0) o.num_clothes = 0;
    o.token = nextToken++;
    strcpy(o.status, "Unwashed");
    enqueue(o);

    printf("\n");
    line(GRN, 'T');
    centered(GRN, "TICKET");
    line(GRN, 'M');
    rowf(GRN, " Token   : #%d", o.token);
    rowf(GRN, " Room    : %d", o.room_num);
    rowf(GRN, " Guest   : %.30s", o.name);
    rowf(GRN, " Pieces  : %d", o.num_clothes);
    rowf(GRN, " Charge  : Tk %d  (%d x Tk %d, payable on delivery)",
         o.num_clothes * RATE, o.num_clothes, RATE);
    rowf(GRN, " Queue # : %d", queueCount());
    line(GRN, 'B');
}

static void processLaundry(void) {
    Laundry cur;
    if (!dequeue(&cur)) {
        printf(YEL "\n   ⚠  The queue is empty — nothing to wash.\n" RST);
        return;
    }
    printf(BOLD "\n   Processing token #%d  (Room %d, %s)\n\n" RST,
           cur.token, cur.room_num, cur.name);
    washAnimation(cur.num_clothes);
    strcpy(cur.status, "Washed & Ironed");
    storageRoot = insertBST(storageRoot, cur);
    printf(GRN "\n   ✓ Room %d moved to STORAGE shelf.\n" RST, cur.room_num);
}

static void checkStatus(void) {
    int room = readInt("Room number to look up :");
    BSTNode *hit = searchBST(storageRoot, room);
    if (hit) {
        printf("\n");
        line(GRN, 'T'); centered(GRN, "READY FOR PICKUP"); line(GRN, 'M');
        rowf(GRN, " Token     : #%d", hit->data.token);
        rowf(GRN, " Guest     : %.30s", hit->data.name);
        rowf(GRN, " Pieces    : %d", hit->data.num_clothes);
        rowf(GRN, " Condition : %s", hit->data.status);
        line(GRN, 'B');
        return;
    }
    int pos = 1;
    for (QueueNode *t = front; t; t = t->next, pos++) {
        if (t->data.room_num == room) {
            printf("\n");
            line(YEL, 'T'); centered(YEL, "STILL IN QUEUE"); line(YEL, 'M');
            rowf(YEL, " Token     : #%d", t->data.token);
            rowf(YEL, " Guest     : %.30s", t->data.name);
            rowf(YEL, " Condition : %s", t->data.status);
            rowf(YEL, " Position  : %d of %d", pos, queueCount());
            line(YEL, 'B');
            return;
        }
    }
    printf(RED "\n   ✗ No record found for room %d.\n" RST, room);
}

static void viewQueue(void) {
    printf("\n");
    line(YEL, 'T'); centered(YEL, "PENDING QUEUE  (front -> rear)"); line(YEL, 'M');
    if (!front) row(YEL, " (empty)");
    int i = 1;
    for (QueueNode *t = front; t; t = t->next, i++)
        rowf(YEL, " %2d. #%d  Room %-5d %-18.18s %2d pcs",
             i, t->data.token, t->data.room_num, t->data.name, t->data.num_clothes);
    line(YEL, 'B');
}

static void viewStorage(void) {
    int n = 0;
    printf("\n");
    line(GRN, 'T'); centered(GRN, "STORAGE SHELF  (sorted by room)"); line(GRN, 'M');
    inorderPrint(storageRoot, &n);
    if (!n) row(GRN, " (empty)");
    line(GRN, 'M');
    rowf(GRN, " %d bundle(s) waiting for pickup", n);
    line(GRN, 'B');
}

static void deliver(void) {
    int room = readInt("Room number to deliver :");
    BSTNode *hit = searchBST(storageRoot, room);
    if (!hit) { printf(RED "\n   ✗ Nothing on the shelf for room %d.\n" RST, room); return; }
    Laundry d = hit->data;
    storageRoot = deleteBST(storageRoot, room);
    int total = d.num_clothes * RATE;

    printf("\n");
    line(MAG, 'T');
    centered(MAG, "L A U N D R Y   B I L L");
    line(MAG, 'M');
    rowf(MAG, " Invoice : #%d", d.token);
    rowf(MAG, " Room    : %-8d Guest : %.24s", d.room_num, d.name);
    line(MAG, 'M');
    rowf(MAG, " %-26s %5s %6s %9s", "ITEM", "QTY", "RATE", "AMOUNT");
    rowf(MAG, " %-26s %5d %6d %9d", "Wash & Iron", d.num_clothes, RATE, total);
    line(MAG, 'M');
    rowf(MAG, " %-26s %22s", "", "-----------");
    rowf(MAG, " %-32s TOTAL : Tk %6d", "", total);
    line(MAG, 'M');
    rowf(MAG, " %d piece(s) handed over. Thank you!", d.num_clothes);
    line(MAG, 'B');
}

int main(void) {
    platform_init();
    for (;;) {
        clearScreen();
        banner();
        menu();
        int choice = readInt("Choice >");
        switch (choice) {
            case 1: receiveOrder();  break;
            case 2: processLaundry();break;
            case 3: checkStatus();   break;
            case 4: viewQueue();     break;
            case 5: viewStorage();   break;
            case 6: deliver();       break;
            case 0:
                printf(CYN "\n   Shutting down. See you!\n\n" RST);
                while (front) { Laundry tmp; dequeue(&tmp); }
                freeBST(storageRoot);
                return 0;
            default:
                printf(RED "\n   ✗ Pick a number from the menu.\n" RST);
        }
        pause_();
    }
}