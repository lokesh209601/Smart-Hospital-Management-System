#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QVector>
#include <QMap>

// Doctor Structure
struct Doctor {
    QString id;
    QString name;
    QString degree;
    QString specialization;
    QString department;
    QString joinDate;
};

// Patient Structure
struct Patient {
    QString id;
    QString name;
    int age;
    QString gender;
    QString phone;
    QString bloodGroup;
    QString address;
    QString registrationDate;
};

// Lab Test Structure
struct LabTest {
    QString patientId;
    QString testType;
    QString testDate;
    QString result;
};

// Ward Admission Structure
struct Admission {
    QString patientId;
    QString wardType;
    int bedNumber;
    QString doctorId;
    QString admissionDate;
    QString dischargeDate;
    bool isActive;
};

// Database Manager
class Database {
public:
    static Database& getInstance();
    
    // Doctor Management
    void addDoctor(const QString &name, const QString &id, const QString &specialization, 
                   const QString &degree, const QString &dept);
    void removeDoctor(const QString &id);
    QVector<Doctor> getAllDoctors();
    Doctor getDoctorById(const QString &id);
    
    // Patient Management
    void addPatient(const QString &name, const QString &id, const QString &age, 
                    const QString &gender, const QString &phone, const QString &bloodGroup, 
                    const QString &address);
    QVector<Patient> getAllPatients();
    Patient getPatientById(const QString &id);
    
    // Lab Test Management
    void addLabTest(const QString &patientId, const QString &testType, const QString &date);
    QVector<LabTest> getLabTestsByPatient(const QString &patientId);
    
    // Ward Admission Management
    void admitPatient(const QString &patientId, const QString &wardType, int bedNo, 
                      const QString &docId);
    void dischargePatient(const QString &patientId);
    QVector<Admission> getActiveAdmissions();
    QVector<Admission> getPatientAdmissions(const QString &patientId);
    
    // Income Calculation
    int getTotalIncome();
    void addIncome(int amount);
    
    // Persistence
    void saveData();
    void loadData();
    
private:
    Database() : totalIncome(0) { loadData(); }
    
    QVector<Doctor> doctors;
    QVector<Patient> patients;
    QVector<LabTest> labTests;
    QVector<Admission> admissions;
    int totalIncome;
};

#endif // DATABASE_H
