#include "Admin.hpp"
#include <limits>

Admin* initialization();
void showMenu();
void addUnconnectedRouter(Admin *admin);
void simulate(Admin *admin);
void sbs(Admin *admin);
void showSubMenu(Admin *admin);

int main() {
    srand(time(nullptr));
    Admin *admin = initialization();
    int option;
    do {
        showMenu();
        cout << "Enter an option: ";
        cin >> option;
        cout << endl;
        if (cin.fail()) {
            cout << "Invalid option" << endl;
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            continue;
        }
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
    do {
        cout<<"Enter the Bandwidth: ";
        cin>>BW;
        cout<<endl;
        if (cin.fail()) {
            cout << "Invalid option" << endl;
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            continue;
        }
        break;
    } while (true);

    admin->setBW(BW);

    int terminals;
    do {
        cout<<"Enter how many terminals per router: ";
        cin>>terminals;
        cout<<endl;
        if (cin.fail()) {
            cout << "Invalid option" << endl;
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            continue;
        }
        break;
    } while (true);
    admin->setTerminals(terminals);
    int routersQuantity;
    do {
        cout<<"Enter the number of routers to create: ";
        cin>>routersQuantity;
        cout<<endl;
        if (cin.fail()) {
            cout << "Invalid option" << endl;
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            continue;
        }
        break;
    } while (true);

    int complexity;
    cout<<"The complexity should be a number between 0 and 20, the higher the number the more complex the network will be"<<endl
        <<"If the number is out of the range, the network will be created with a complexity of 1"<<endl;
    do {
        cout<<"Enter the complexity of the network: ";
        cin>>complexity;
        cout<<endl;
        if (cin.fail()) {
            cout << "Invalid option" << endl;
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            continue;
        }
        break;
    } while (true);
    admin->randomNetwork(routersQuantity, complexity);
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
    cout << "Router added" << endl;
    auto *router = admin->getRouters()->getTailData();
    cout<<"Choose a router to connect the new router to"<<endl;
    bool end = false;
    do {
        cout<<"Available routers to connect to: [0-"<<admin->getRouters()->getNodeCount()-2<<"]"<<endl;
        int option;
        cin>>option;
        if (option < 0 || option > admin->getRouters()->getNodeCount()-2) {
            cout<<"Invalid option"<<endl;
            continue;
        } else {
            admin->getNetwork()->connectRouters(router, admin->getRouters()->getDataAtNode(option));
            cout<<"Do you want to add another connection? (y/n)"<<endl;
            char c;
            cin>>c;
            if (c == 'y' || c == 'Y') {
                continue;
            } else {
                end = true;
            }
        }
    } while (!end);
    admin->getNetwork()->recalculateRoutes();
}

void simulate(Admin *admin) {
    bool end = false;
    do {
        admin->sendPages();
        admin->sendFromQueues();
        admin->checkCounter();
        admin->printRouters();
        cout<<"Do you want to simulate next iteration? (y/n)"<<endl;
        char c;
        cin>>c;
        if (c == 'y' || c == 'Y') {
            continue;
        } else {
            end = true;
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
        if (cin.fail()) {
            cout << "Invalid option" << endl;
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            continue;
        }
        switch (subOption) {
            case 1:
                int bw;
                cout << "Enter the new Bandwidth: ";
                cin >> bw;
                admin->setBW(bw);
                break;
            case 2:
                int pl;
                cout << "Enter the new maximum page length: " << endl;
                cin >> pl;
                admin->setMaxPageLength(pl);
                break;
            case 3:
                int tpr;
                cout << "Enter the new number of terminals per router (should be higher than the current): " << endl;
                cin >> tpr;
                admin->setTerminals(tpr);
                admin->setRoutersTerminals();
                break;
            case 4:
                int prob;
                cout << "Enter the new probability for a Terminal to send a page (0-100): " << endl;
                cin >> prob;
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