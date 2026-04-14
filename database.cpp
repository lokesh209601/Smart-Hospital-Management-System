#include "database.h"
#include <QDate>
#include <QFile>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QCoreApplication>

static QString getDataFilePath()
{
    QString dir = QCoreApplication::applicationDirPath();
    return QDir(dir).filePath("hospital_data.json");
}

Database& Database::getInstance()
{
    static Database instance;
    return instance;
}

// ============ Doctor Management ============
void Database::addDoctor(const QString &name, const QString &id, const QString &specialization, 
                         const QString &degree, const QString &dept)
{
    Doctor doc;
    doc.name = name;
    doc.id = id;
    doc.specialization = specialization;
    doc.degree = degree;
    doc.department = dept;
    doc.joinDate = QDate::currentDate().toString("dd/MM/yyyy");
    
    doctors.append(doc);
    totalIncome += 50000; // Add income for hiring doctor
}

void Database::removeDoctor(const QString &id)
{
    for (int i = 0; i < doctors.size(); ++i) {
        if (doctors[i].id == id) {
            doctors.removeAt(i);
            break;
        }
    }
}

QVector<Doctor> Database::getAllDoctors()
{
    return doctors;
}

Doctor Database::getDoctorById(const QString &id)
{
    for (const auto &doc : doctors) {
        if (doc.id == id) {
            return doc;
        }
    }
    return Doctor(); // Return empty doctor if not found
}

// ============ Patient Management ============
void Database::addPatient(const QString &name, const QString &id, const QString &age, 
                          const QString &gender, const QString &phone, const QString &bloodGroup, 
                          const QString &address)
{
    Patient patient;
    patient.name = name;
    patient.id = id;
    patient.age = age.toInt();
    patient.gender = gender;
    patient.phone = phone;
    patient.bloodGroup = bloodGroup;
    patient.address = address;
    patient.registrationDate = QDate::currentDate().toString("dd/MM/yyyy");
    
    patients.append(patient);
    totalIncome += 5000; // Add income for patient registration
}

QVector<Patient> Database::getAllPatients()
{
    return patients;
}

Patient Database::getPatientById(const QString &id)
{
    for (const auto &patient : patients) {
        if (patient.id == id) {
            return patient;
        }
    }
    return Patient(); // Return empty patient if not found
}

// ============ Lab Test Management ============
void Database::addLabTest(const QString &patientId, const QString &testType, const QString &date)
{
    LabTest test;
    test.patientId = patientId;
    test.testType = testType;
    test.testDate = date;
    test.result = "Pending";
    
    labTests.append(test);
    
    // Add income based on test type
    if (testType == "Blood Test" || testType == "Urine Test") {
        totalIncome += 1000;
    } else if (testType == "X-Ray" || testType == "Ultrasound") {
        totalIncome += 2000;
    } else if (testType == "CT Scan" || testType == "MRI") {
        totalIncome += 5000;
    } else {
        totalIncome += 1500;
    }
}

QVector<LabTest> Database::getLabTestsByPatient(const QString &patientId)
{
    QVector<LabTest> patientTests;
    for (const auto &test : labTests) {
        if (test.patientId == patientId) {
            patientTests.append(test);
        }
    }
    return patientTests;
}

// ============ Ward Admission Management ============
void Database::admitPatient(const QString &patientId, const QString &wardType, int bedNo, 
                            const QString &docId)
{
    Admission admission;
    admission.patientId = patientId;
    admission.wardType = wardType;
    admission.bedNumber = bedNo;
    admission.doctorId = docId;
    admission.admissionDate = QDate::currentDate().toString("dd/MM/yyyy");
    admission.dischargeDate = "";
    admission.isActive = true;
    
    admissions.append(admission);
    
    // Add income based on ward type
    if (wardType == "ICU") {
        totalIncome += 10000;
    } else if (wardType == "Private Ward") {
        totalIncome += 8000;
    } else {
        totalIncome += 5000;
    }
}

void Database::dischargePatient(const QString &patientId)
{
    for (auto &admission : admissions) {
        if (admission.patientId == patientId && admission.isActive) {
            admission.isActive = false;
            admission.dischargeDate = QDate::currentDate().toString("dd/MM/yyyy");
            break;
        }
    }
}

QVector<Admission> Database::getActiveAdmissions()
{
    QVector<Admission> active;
    for (const auto &admission : admissions) {
        if (admission.isActive) {
            active.append(admission);
        }
    }
    return active;
}

QVector<Admission> Database::getPatientAdmissions(const QString &patientId)
{
    QVector<Admission> patientAdmissions;
    for (const auto &admission : admissions) {
        if (admission.patientId == patientId) {
            patientAdmissions.append(admission);
        }
    }
    return patientAdmissions;
}

// ============ Income Management ============
int Database::getTotalIncome()
{
    return totalIncome;
}

void Database::addIncome(int amount)
{
    totalIncome += amount;
}

void Database::saveData()
{
    QJsonObject root;

    QJsonArray doctorArray;
    for (const auto &doc : doctors) {
        QJsonObject obj;
        obj["id"] = doc.id;
        obj["name"] = doc.name;
        obj["degree"] = doc.degree;
        obj["specialization"] = doc.specialization;
        obj["department"] = doc.department;
        obj["joinDate"] = doc.joinDate;
        doctorArray.append(obj);
    }
    root["doctors"] = doctorArray;

    QJsonArray patientArray;
    for (const auto &patient : patients) {
        QJsonObject obj;
        obj["id"] = patient.id;
        obj["name"] = patient.name;
        obj["age"] = patient.age;
        obj["gender"] = patient.gender;
        obj["phone"] = patient.phone;
        obj["bloodGroup"] = patient.bloodGroup;
        obj["address"] = patient.address;
        obj["registrationDate"] = patient.registrationDate;
        patientArray.append(obj);
    }
    root["patients"] = patientArray;

    QJsonArray labArray;
    for (const auto &test : labTests) {
        QJsonObject obj;
        obj["patientId"] = test.patientId;
        obj["testType"] = test.testType;
        obj["testDate"] = test.testDate;
        obj["result"] = test.result;
        labArray.append(obj);
    }
    root["labTests"] = labArray;

    QJsonArray admissionArray;
    for (const auto &admission : admissions) {
        QJsonObject obj;
        obj["patientId"] = admission.patientId;
        obj["wardType"] = admission.wardType;
        obj["bedNumber"] = admission.bedNumber;
        obj["doctorId"] = admission.doctorId;
        obj["admissionDate"] = admission.admissionDate;
        obj["dischargeDate"] = admission.dischargeDate;
        obj["isActive"] = admission.isActive;
        admissionArray.append(obj);
    }
    root["admissions"] = admissionArray;
    root["totalIncome"] = totalIncome;

    QJsonDocument document(root);
    QFile file(getDataFilePath());
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(document.toJson(QJsonDocument::Indented));
        file.close();
    }
}

void Database::loadData()
{
    QFile file(getDataFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(data);
    if (!document.isObject()) {
        return;
    }

    QJsonObject root = document.object();

    doctors.clear();
    patients.clear();
    labTests.clear();
    admissions.clear();
    totalIncome = root.value("totalIncome").toInt();

    QJsonArray doctorArray = root.value("doctors").toArray();
    for (const auto &value : doctorArray) {
        QJsonObject obj = value.toObject();
        Doctor doc;
        doc.id = obj.value("id").toString();
        doc.name = obj.value("name").toString();
        doc.degree = obj.value("degree").toString();
        doc.specialization = obj.value("specialization").toString();
        doc.department = obj.value("department").toString();
        doc.joinDate = obj.value("joinDate").toString();
        doctors.append(doc);
    }

    QJsonArray patientArray = root.value("patients").toArray();
    for (const auto &value : patientArray) {
        QJsonObject obj = value.toObject();
        Patient patient;
        patient.id = obj.value("id").toString();
        patient.name = obj.value("name").toString();
        patient.age = obj.value("age").toInt();
        patient.gender = obj.value("gender").toString();
        patient.phone = obj.value("phone").toString();
        patient.bloodGroup = obj.value("bloodGroup").toString();
        patient.address = obj.value("address").toString();
        patient.registrationDate = obj.value("registrationDate").toString();
        patients.append(patient);
    }

    QJsonArray labArray = root.value("labTests").toArray();
    for (const auto &value : labArray) {
        QJsonObject obj = value.toObject();
        LabTest test;
        test.patientId = obj.value("patientId").toString();
        test.testType = obj.value("testType").toString();
        test.testDate = obj.value("testDate").toString();
        test.result = obj.value("result").toString();
        labTests.append(test);
    }

    QJsonArray admissionArray = root.value("admissions").toArray();
    for (const auto &value : admissionArray) {
        QJsonObject obj = value.toObject();
        Admission admission;
        admission.patientId = obj.value("patientId").toString();
        admission.wardType = obj.value("wardType").toString();
        admission.bedNumber = obj.value("bedNumber").toInt();
        admission.doctorId = obj.value("doctorId").toString();
        admission.admissionDate = obj.value("admissionDate").toString();
        admission.dischargeDate = obj.value("dischargeDate").toString();
        admission.isActive = obj.value("isActive").toBool();
        admissions.append(admission);
    }
}

