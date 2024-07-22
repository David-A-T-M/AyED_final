#include "Admin.hpp"
#include <limits>

Admin* initialization();
void showMenu();
void addUnconnectedRouter(Admin *admin);
void simulate(Admin *admin);

int main() {
    srand(time(nullptr));
    Admin *admin = initialization();
    showMenu();
    int option;
    do {
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
                admin->printRouters();
                break;
            case 3:
                simulate(admin);
                break;
            case 4:
                int bw;
                cout << "Enter the Bandwidth: ";
                cin >> bw;
                admin->setBW(bw);
                break;
            case 5:
                int nbw;
                cout << "Enter the Bandwidth: ";
                cin >> nbw;
                cout << endl;
                admin->setBW(nbw);
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
    cout << "4. Set New Bandwidth" << endl;
    cout << "5. Exit" << endl;
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
}

void simulate(Admin *admin) {
    bool end = false;
    do {
        cout<<"a"<<endl;
        admin->sendPages();
        cout<<"a"<<endl;
        admin->sendFromQueues();
        cout<<"a"<<endl;
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