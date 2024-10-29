#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Bankomat {
private:
    string id; 
    int balance; 
    int minWithdraw;
    int maxWithdraw; 

    int denominations[5];

public:
    Bankomat(string atmId, int minLimit, int maxLimit) : id(atmId), balance(0), minWithdraw(minLimit), maxWithdraw(maxLimit) {
        for (int i = 0; i < 5; i++) {
            denominations[i] = 0;
        }
    }
    
    void loadMoney(int count100, int count200, int count500, int count1000) {
        denominations[0] += count100;
        denominations[1] += count200;
        denominations[2] += count500;
        denominations[3] += count1000;
        balance += count100 * 100 + count200 * 200 + count500 * 500 + count1000 * 1000;
    }

    bool withdrawMoney(int amount) {
        cout << "Required amount to be issued: " << amount << endl;

        if (amount < minWithdraw || amount > maxWithdraw) {
            cout << "Withdrawal amount must be between " << minWithdraw << " and " << maxWithdraw << ".\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient funds in ATM.\n";
            return false;
        }

        balance -= amount;
        
        int remainingAmount = amount;
        int bills[4] = { 1000, 500, 200, 100 };
        int dispensed[4] = { 0, 0, 0, 0 };

        for (int i = 0; i < 4; i++) {
            while (remainingAmount >= bills[i] && denominations[i] > 0) {
                remainingAmount -= bills[i];
                denominations[i]--;
                dispensed[i]++;
            }
        }
        if (remainingAmount > 0) { 
            cout << "Unable to dispense the exact amount with available denominations.\n";
            return false;
        }

        cout << "Dispensed bills:\n";
        for (int i = 0; i < 4; i++) {
            if (dispensed[i] > 0) {
                cout << bills[i] << ": " << dispensed[i] << " bills\n";
            }
        }
        
        cout << "Withdrawal successful.\n";

        return true;
    }

    string toString() const {
        stringstream ss;
        ss << "\tATM condition\t\n" << "ATM ID: " << id << "\nBalance: " << balance << "\n";
        ss << "Denominations:\n";
        ss << "100: " << denominations[3] << ", 200: " << denominations[2]
            << ", 500: " << denominations[1] << ", 1000: " << denominations[0] << "\n";
        return ss.str();
    }
};

int main() {
    // Инициализируем банкомат с идентификационным номером и минимальной/максимальной суммой снятия
    Bankomat atm("ATM123", 1000, 5000);

    // Загружаем купюры в банкомат
    atm.loadMoney(10, 5, 2, 3);
    cout << atm.toString() << endl;

    // Пытаемся снять деньги
    if (atm.withdrawMoney(1500)) {
        cout << endl;
        cout << atm.toString() << endl;
    }

    // Пытаемся снять неверную сумму
    if (atm.withdrawMoney(7000)) {
        cout << endl;
        cout << atm.toString() << endl;
    }

    return 0;
}