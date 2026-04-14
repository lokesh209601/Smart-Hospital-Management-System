#include "dialogs.h"
#include <QMessageBox>
#include <QHeaderView>

// ============ Doctor Hiring Dialog ============
DoctorHiringDialog::DoctorHiringDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Hire New Doctor");
    setGeometry(100, 100, 400, 300);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Name
    layout->addWidget(new QLabel("Full Name:"));
    nameEdit = new QLineEdit();
    layout->addWidget(nameEdit);
    
    // ID
    layout->addWidget(new QLabel("Doctor ID:"));
    idEdit = new QLineEdit();
    layout->addWidget(idEdit);
    
    // Degree
    layout->addWidget(new QLabel("Degree:"));
    degreeEdit = new QLineEdit();
    layout->addWidget(degreeEdit);
    
    // Specialization
    layout->addWidget(new QLabel("Specialization:"));
    specializationCombo = new QComboBox();
    specializationCombo->addItems({"Cardiology", "Neurology", "Orthopedics", "Pediatrics", 
                                    "Dermatology", "General Medicine", "Surgery", "ENT"});
    layout->addWidget(specializationCombo);
    
    // Department
    layout->addWidget(new QLabel("Department:"));
    deptCombo = new QComboBox();
    deptCombo->addItems({"Emergency", "IPD (In-Patient)", "OPD (Out-Patient)", "ICU", "Surgery"});
    layout->addWidget(deptCombo);
    
    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    submitBtn = new QPushButton("Hire");
    cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(submitBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);
    
    connect(submitBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

bool DoctorHiringDialog::getDoctorData(QString &name, QString &id, QString &specialization, 
                                        QString &degree, QString &dept)
{
    if (exec() == QDialog::Accepted) {
        if (nameEdit->text().isEmpty() || idEdit->text().isEmpty() || degreeEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all fields!");
            return false;
        }
        name = nameEdit->text();
        id = idEdit->text();
        specialization = specializationCombo->currentText();
        degree = degreeEdit->text();
        dept = deptCombo->currentText();
        return true;
    }
    return false;
}

// ============ Patient Registration Dialog ============
PatientRegistrationDialog::PatientRegistrationDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Register New Patient");
    setGeometry(100, 100, 400, 400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Name
    layout->addWidget(new QLabel("Full Name:"));
    nameEdit = new QLineEdit();
    layout->addWidget(nameEdit);
    
    // Patient ID
    layout->addWidget(new QLabel("Patient ID:"));
    idEdit = new QLineEdit();
    layout->addWidget(idEdit);
    
    // Age
    layout->addWidget(new QLabel("Age:"));
    ageSpinBox = new QSpinBox();
    ageSpinBox->setRange(0, 150);
    layout->addWidget(ageSpinBox);
    
    // Gender
    layout->addWidget(new QLabel("Gender:"));
    genderCombo = new QComboBox();
    genderCombo->addItems({"Male", "Female", "Other"});
    layout->addWidget(genderCombo);
    
    // Phone
    layout->addWidget(new QLabel("Phone Number:"));
    phoneEdit = new QLineEdit();
    layout->addWidget(phoneEdit);
    
    // Blood Group
    layout->addWidget(new QLabel("Blood Group:"));
    bloodGroupCombo = new QComboBox();
    bloodGroupCombo->addItems({"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"});
    layout->addWidget(bloodGroupCombo);
    
    // Address
    layout->addWidget(new QLabel("Address:"));
    addressEdit = new QLineEdit();
    layout->addWidget(addressEdit);
    
    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    submitBtn = new QPushButton("Register");
    cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(submitBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);
    
    connect(submitBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

bool PatientRegistrationDialog::getPatientData(QString &name, QString &id, QString &age, 
                                               QString &gender, QString &phone, 
                                               QString &bloodGroup, QString &address)
{
    if (exec() == QDialog::Accepted) {
        if (nameEdit->text().isEmpty() || idEdit->text().isEmpty() || phoneEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all required fields!");
            return false;
        }
        name = nameEdit->text();
        id = idEdit->text();
        age = QString::number(ageSpinBox->value());
        gender = genderCombo->currentText();
        phone = phoneEdit->text();
        bloodGroup = bloodGroupCombo->currentText();
        address = addressEdit->text();
        return true;
    }
    return false;
}

// ============ Lab Test Dialog ============
LabTestDialog::LabTestDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Schedule Lab Test");
    setGeometry(100, 100, 350, 200);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Patient ID
    layout->addWidget(new QLabel("Patient ID:"));
    patientIdEdit = new QLineEdit();
    layout->addWidget(patientIdEdit);
    
    // Test Type
    layout->addWidget(new QLabel("Test Type:"));
    testTypeCombo = new QComboBox();
    testTypeCombo->addItems({"Blood Test", "Urine Test", "X-Ray", "Ultrasound", 
                             "CT Scan", "ECG", "MRI", "COVID Test"});
    layout->addWidget(testTypeCombo);
    
    // Date
    layout->addWidget(new QLabel("Test Date:"));
    dateEdit = new QDateEdit();
    dateEdit->setDate(QDate::currentDate().addDays(1));
    layout->addWidget(dateEdit);
    
    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    submitBtn = new QPushButton("Schedule");
    cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(submitBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);
    
    connect(submitBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

bool LabTestDialog::getTestData(QString &patientId, QString &testType, QString &date)
{
    if (exec() == QDialog::Accepted) {
        if (patientIdEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please enter Patient ID!");
            return false;
        }
        patientId = patientIdEdit->text();
        testType = testTypeCombo->currentText();
        date = dateEdit->date().toString("dd/MM/yyyy");
        return true;
    }
    return false;
}

// ============ Ward Admission Dialog ============
WardAdmissionDialog::WardAdmissionDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Admit Patient to Ward");
    setGeometry(100, 100, 400, 300);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    // Patient ID
    layout->addWidget(new QLabel("Patient ID:"));
    patientIdEdit = new QLineEdit();
    layout->addWidget(patientIdEdit);
    
    // Ward Type
    layout->addWidget(new QLabel("Ward Type:"));
    wardTypeCombo = new QComboBox();
    wardTypeCombo->addItems({"General Ward", "Private Ward", "ICU", "Semi-Private"});
    layout->addWidget(wardTypeCombo);
    
    // Bed Number
    layout->addWidget(new QLabel("Bed Number:"));
    bedNoSpinBox = new QSpinBox();
    bedNoSpinBox->setRange(1, 100);
    layout->addWidget(bedNoSpinBox);
    
    // Doctor ID
    layout->addWidget(new QLabel("Assigned Doctor ID:"));
    docIdEdit = new QLineEdit();
    layout->addWidget(docIdEdit);
    
    // Admission Date
    layout->addWidget(new QLabel("Admission Date:"));
    admitDateEdit = new QDateEdit();
    admitDateEdit->setDate(QDate::currentDate());
    layout->addWidget(admitDateEdit);
    
    // Buttons
    QHBoxLayout *btnLayout = new QHBoxLayout();
    submitBtn = new QPushButton("Admit");
    cancelBtn = new QPushButton("Cancel");
    btnLayout->addWidget(submitBtn);
    btnLayout->addWidget(cancelBtn);
    layout->addLayout(btnLayout);
    
    connect(submitBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
}

bool WardAdmissionDialog::getAdmissionData(QString &patientId, QString &wardType, 
                                           QString &bedNo, QString &docId)
{
    if (exec() == QDialog::Accepted) {
        if (patientIdEdit->text().isEmpty() || docIdEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill all required fields!");
            return false;
        }
        patientId = patientIdEdit->text();
        wardType = wardTypeCombo->currentText();
        bedNo = QString::number(bedNoSpinBox->value());
        docId = docIdEdit->text();
        return true;
    }
    return false;
}

// ============ Search/View Dialog ============
SearchDialog::SearchDialog(const QString &title, const QStringList &headers, QWidget *parent) 
    : QDialog(parent)
{
    setWindowTitle(title);
    setGeometry(50, 50, 700, 400);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    table = new QTableWidget();
    table->setColumnCount(headers.size());
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    layout->addWidget(table);
    
    QPushButton *closeBtn = new QPushButton("Close");
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);
    layout->addWidget(closeBtn);
}

void SearchDialog::addRow(const QStringList &rowData)
{
    int row = table->rowCount();
    table->insertRow(row);
    
    for (int col = 0; col < rowData.size(); ++col) {
        table->setItem(row, col, new QTableWidgetItem(rowData[col]));
    }
}

void SearchDialog::clearTable()
{
    table->setRowCount(0);
}
