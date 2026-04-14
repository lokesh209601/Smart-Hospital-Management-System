#ifndef DIALOGS_H
#define DIALOGS_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDateEdit>

// Doctor Hiring Dialog
class DoctorHiringDialog : public QDialog
{
public:
    DoctorHiringDialog(QWidget *parent = nullptr);
    bool getDoctorData(QString &name, QString &id, QString &specialization, QString &degree, QString &dept);

private:
    QLineEdit *nameEdit;
    QLineEdit *idEdit;
    QLineEdit *degreeEdit;
    QComboBox *specializationCombo;
    QComboBox *deptCombo;
    QPushButton *submitBtn;
    QPushButton *cancelBtn;
};

// Patient Registration Dialog
class PatientRegistrationDialog : public QDialog
{
public:
    PatientRegistrationDialog(QWidget *parent = nullptr);
    bool getPatientData(QString &name, QString &id, QString &age, QString &gender, 
                       QString &phone, QString &bloodGroup, QString &address);

private:
    QLineEdit *nameEdit;
    QLineEdit *idEdit;
    QSpinBox *ageSpinBox;
    QComboBox *genderCombo;
    QLineEdit *phoneEdit;
    QComboBox *bloodGroupCombo;
    QLineEdit *addressEdit;
    QPushButton *submitBtn;
    QPushButton *cancelBtn;
};

// Lab Test Scheduling Dialog
class LabTestDialog : public QDialog
{
public:
    LabTestDialog(QWidget *parent = nullptr);
    bool getTestData(QString &patientId, QString &testType, QString &date);

private:
    QLineEdit *patientIdEdit;
    QComboBox *testTypeCombo;
    QDateEdit *dateEdit;
    QPushButton *submitBtn;
    QPushButton *cancelBtn;
};

// Ward Admission Dialog
class WardAdmissionDialog : public QDialog
{
public:
    WardAdmissionDialog(QWidget *parent = nullptr);
    bool getAdmissionData(QString &patientId, QString &wardType, QString &bedNo, QString &docId);

private:
    QLineEdit *patientIdEdit;
    QComboBox *wardTypeCombo;
    QSpinBox *bedNoSpinBox;
    QLineEdit *docIdEdit;
    QDateEdit *admitDateEdit;
    QPushButton *submitBtn;
    QPushButton *cancelBtn;
};

// Search/View Dialog
class SearchDialog : public QDialog
{
public:
    SearchDialog(const QString &title, const QStringList &headers, QWidget *parent = nullptr);
    void addRow(const QStringList &rowData);
    void clearTable();

private:
    QTableWidget *table;
};

#endif // DIALOGS_H
