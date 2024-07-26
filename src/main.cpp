#include "Admin.hpp"
#include <limits>

Admin* initialization();
void showMenu();
void addUnconnectedRouter(Admin *admin);
void simulate(Admin *admin);
void sbs(Admin *admin);
void showSubMenu(Admin *admin);
void validateInput(int &input, int min = numeric_limits<int>::min(), int max = numeric_limits<int>::max());

int main() {
    srand(time(nullptr));
    Admin *admin = initialization();
    int option;
    do {
        showMenu();
        cout << "Enter an option: ";
        validateInput(option, 1, 6);
        switch (option) {
            case 1:
                addUnconnectedRouter(admin);
                admin->printRouters();
                break;
            case 2:
                admin->addRandomlyConnectedRouter();
                admin->getNetwork()->recalculateRoutes();
                admin->printRouters();
                break;
            case 3:
                simulate(admin);
                break;
            case 4:
                showSubMenu(admin);
                break;
            case 5:
                break;
            case 6:
                cout << "Step by step: " << endl;
                sbs(admin);
                break;

            default:
                cout << "Invalid option" << endl;
                break;
        }
    } while (option != 5);

    return 0;
}

Admin* initialization() {
    cout << "WELCOME" << endl;
    cout << "Press ENTER to start" << endl;
    cin.get();
    auto *admin = new Admin();

    int BW;
    cout << "Set the Bandwidth: ";
    validateInput(BW, 1);
    admin->setBW(BW);
    cout << endl;

    int terminals;
    cout << "Set the number of terminals per router: ";
    validateInput(terminals, 1, 256);
    admin->setTerminals(terminals);
    cout << endl;

    int routersQuantity;
    cout << "Set the number of routers: ";
    validateInput(routersQuantity, 1, 256);
    cout << endl;

    int complexity;
    cout<<"The complexity should be a number between 0 and 20, the higher the number the more complex the network will be"<<endl
        <<"Enter the complexity: ";
    validateInput(complexity, 0, 20);
    admin->randomNetwork(routersQuantity, complexity);
    cout << endl;

    cout<<"The network has been created"<<endl;
    admin->getNetwork()->recalculateRoutes();
    admin->printRouters();
    return admin;
}

void showMenu() {
    cout << "1. Add unconnected router" << endl;
    cout << "2. Add randomly connected router" << endl;
    cout << "3. Simulation" << endl;
    cout << "4. Customization options" << endl;
    cout << "5. Exit" << endl;
    cout << "6. Step by step" << endl;
}

void addUnconnectedRouter(Admin *admin) {
    admin->addUnconnectedRouter();
    cout << "Router created" << endl;
    auto *router = admin->getRouters()->getTailData();
    cout<<"Available routers to connect to: [0-"<<admin->getRouters()->getNodeCount()-2<<"]"<<endl;
    do {
        int option;
        cout<<"Choose a router to connect the new router to"<<endl;
        validateInput(option, 0, admin->getRouters()->getNodeCount()-2);
        admin->getNetwork()->connectRouters(router, admin->getRouters()->getDataAtNode(option));
        cout<<"Do you want to add another connection? (y/n)"<<endl;
        char c;
        cin>>c;
        if (c == 'y' || c == 'Y') {
            continue;
        } else {
            break;
        }
    } while (true);

    admin->getNetwork()->recalculateRoutes();
}

void simulate(Admin *admin) {
    bool end = false;
    do {
        admin->sendPages();
        admin->sendFromQueues();
        admin->checkCounter();
        admin->printRouters();
        char c;
        bool validInput = false;

        while (!validInput) {
            cout << "Do you want to simulate next iteration? (y/n)" << endl;
            cin >> c;
            if (c == 'y' || c == 'Y') {
                validInput = true;
                continue;
            } else if (c == 'n' || c == 'N') {
                validInput = true;
                end = true;
            } else {
                cout << "Invalid option" << endl;
            }
        }
    } while (!end);
}

void sbs(Admin *admin) {
    char c;
    do {
        admin->sendPages();
        admin->printRouters();
        cout<<"Send from Queues? (y/n)"<<endl;
        cin>>c;
        if (c != 'y' && c != 'Y')
            break;

        admin->sendFromQueues();
        admin->printRouters();
        cout<<"Check for recalculation? (y/n)"<<endl;
        cin>>c;
        if (c != 'y' && c != 'Y')
            break;
        if (admin->checkCounter()) {
            admin->printRouters();
            cout<<"Send new pages? (y/n)"<<endl;
            cin>>c;
            if (c != 'y' && c != 'Y')
                break;
        } else {
            cout<<"No need to recalculate"<<endl;
            cout<<"Send new pages? (y/n)"<<endl;
            cin>>c;
            if (c != 'y' && c != 'Y')
                break;
        }
    } while (true);
}

void showSubMenu(Admin *admin) {
    int subOption;
    do {
        cout << "Submenu:" << endl;
        cout << "1. Set Bandwidth" << endl;
        cout << "2. Set maximum page length" << endl;
        cout << "3. Set Number of terminals per router" << endl;
        cout << "4. Set the Probability to send a page" << endl;
        cout << "5. Back to Main Menu" << endl;
        cout << "Enter an option: ";
        cin >> subOption;
        cout << endl;
        validateInput(subOption, 1, 5);
        switch (subOption) {
            case 1:
                int bw;
                cout << "Enter the new Bandwidth: ";
                validateInput(bw, 1);
                admin->setBW(bw);
                break;
            case 2:
                int pl;
                cout << "Enter the new maximum page length: " << endl;
                validateInput(pl, 1);
                admin->setMaxPageLength(pl);
                break;
            case 3:
                int tpr;
                cout << "Enter the new number of terminals per router (should be higher than the current): " << endl;
                validateInput(tpr);
                admin->setTerminals(tpr);
                admin->setRoutersTerminals();
                break;
            case 4:
                int prob;
                cout << "Enter the new probability for a Terminal to send a page (0-100): " << endl;
                validateInput(prob, 0, 100);
                admin->setProbability(prob);
                break;
            case 5:
                cout << "Returning to main menu..." << endl;
                return;
            default:
                cout << "Invalid option" << endl;
                break;
        }
    } while (subOption != 5);
}

void validateInput(int &input, int min, int max) {
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cout << "Invalid input: ";
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        } else if (input < min || input > max) {
            cout << "Input out of range (" << min << " - " << max << "). Please enter again: ";
        } else {
            break;
        }
    }
}