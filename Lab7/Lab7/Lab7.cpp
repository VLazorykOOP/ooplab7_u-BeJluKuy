#include <iostream>
#include <vector>
#include <string>

class Exam {
private:
    std::string subject;  // Предмет
    int grade;  // Оцінка

public:
    // Конструктор
    Exam(const std::string& subject, int grade) : subject(subject), grade(grade) {}

    // Метод для отримання оцінки
    int getGrade() const {
        return grade;
    }

    // Метод для виведення інформації про екзамен
    void display() const {
        std::cout << "Предмет: " << subject << ", Оцінка: " << grade << std::endl;
    }
};

class Applicant {
private:
    std::string name;  // Ім'я абітурієнта
    std::string faculty;  // Факультет
    std::vector<Exam> exams;  // Вектор екзаменів

public:
    // Конструктор
    Applicant(const std::string& name, const std::string& faculty) : name(name), faculty(faculty) {}

    // Метод для отримання імені абітурієнта
    const std::string& getName() const {
        return name;
    }

    // Метод для додавання екзамену
    void addExam(const std::string& subject, int grade) {
        exams.push_back(Exam(subject, grade));
    }

    // Метод для виведення інформації про абітурієнта
    void display() const {
        std::cout << "Абітурієнт: " << name << std::endl;
        std::cout << "Факультет: " << faculty << std::endl;
        std::cout << "Оцінки:" << std::endl;
        for (const Exam& exam : exams) {
            exam.display();
        }
    }

    // Метод для розрахунку середнього балу
    double calculateAverageGrade() const {
        double sum = 0.0;
        for (const Exam& exam : exams) {
            sum += exam.getGrade();
        }
        return sum / exams.size();
    }
};

class AdmissionSystem {
private:
    std::vector<Applicant> applicants;  // Вектор абітурієнтів

public:
    // Метод для реєстрації абітурієнта
    void registerApplicant(const std::string& name, const std::string& faculty) {
        applicants.push_back(Applicant(name, faculty));
    }

    // Метод для отримання вектора абітурієнтів
    std::vector<Applicant>& getApplicants() {
        return applicants;
    }

    // Метод для отримання вектора зарахованих абітурієнтів за мінімальним середнім балом
    std::vector<Applicant> getAdmittedApplicants(double minimumAverageGrade) const {
        std::vector<Applicant> admittedApplicants;
        for (const Applicant& applicant : applicants) {
            double averageGrade = applicant.calculateAverageGrade();
            if (averageGrade >= minimumAverageGrade) {
                admittedApplicants.push_back(applicant);
            }
        }
        return admittedApplicants;
    }
};

// Функція для виведення меню
void displayMenu() {
    std::cout << "===== Меню Автоматизованої Системи =====" << std::endl;
    std::cout << "1. Зареєструвати абітурієнта" << std::endl;
    std::cout << "2. Вивести список абітурієнтів" << std::endl;
    std::cout << "3. Додати оцінку абітурієнту" << std::endl;
    std::cout << "4. Вивести зарахованих абітурієнтів" << std::endl;
    std::cout << "5. Вийти з програми" << std::endl;
    std::cout << "========================================" << std::endl;
}

int main() {
    AdmissionSystem admissionSystem;  // Об'єкт системи прийому

    std::string name, faculty, subject;
    int choice, grade;

    while (true) {
        displayMenu();  // Виведення меню
        std::cout << "Виберіть опцію: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Зареєструвати абітурієнта:" << std::endl;
            std::cout << "Введіть ім'я: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введіть факультет: ";
            std::getline(std::cin, faculty);

            admissionSystem.registerApplicant(name, faculty);  // Реєстрація абітурієнта
            break;
        case 2:
            std::cout << "Список абітурієнтів:" << std::endl;
            for (const Applicant& applicant : admissionSystem.getApplicants()) {
                applicant.display();  // Виведення інформації про абітурієнта
                std::cout << "Середній бал: " << applicant.calculateAverageGrade() << std::endl;  // Розрахунок середнього балу
                std::cout << std::endl;
            }
            break;
        case 3:
            std::cout << "Додати оцінку абітурієнту:" << std::endl;
            std::cout << "Введіть ім'я абітурієнта: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введіть предмет: ";
            std::getline(std::cin, subject);
            std::cout << "Введіть оцінку: ";
            std::cin >> grade;

            // Пошук абітурієнта за іменем та додавання оцінки
            for (Applicant& applicant : admissionSystem.getApplicants()) {
                if (applicant.getName() == name) {
                    applicant.addExam(subject, grade);
                    break;
                }
            }
            break;
        case 4:
            std::cout << "Зараховані абітурієнти:" << std::endl;
            std::cout << "Введіть мінімальний середній бал: ";
            std::cin >> grade;

            // Отримання зарахованих абітурієнтів та виведення їх інформації
            for (const Applicant& applicant : admissionSystem.getAdmittedApplicants(grade)) {
                applicant.display();
                std::cout << "Середній бал: " << applicant.calculateAverageGrade() << std::endl;
                std::cout << std::endl;
            }
            break;
        case 5:
            std::cout << "Програма завершена." << std::endl;
            return 0;
        default:
            std::cout << "Невірний вибір. Спробуйте ще раз." << std::endl;
        }
    }
}