#include "mainwindow.h"
#include "dialogs.h"
#include "database.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QInputDialog>
#include <QDate>
#include <QPainter>
#include <QRadialGradient>
#include <QScrollArea>
#include <QCloseEvent>

static QPixmap createHospitalLogoPixmap()
{
    QPixmap pix(120, 120);
    pix.fill(Qt::transparent);

    QPainter painter(&pix);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRadialGradient gradient(60, 60, 60);
    gradient.setColorAt(0.0, QColor(255, 255, 255, 240));
    gradient.setColorAt(1.0, QColor(33, 150, 243, 200));
    painter.setBrush(QBrush(gradient));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, 120, 120);

    QPen pen(Qt::white, 12, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawLine(60, 30, 60, 90);
    painter.drawLine(30, 60, 90, 60);
    painter.end();

    return pix;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Hospital Management System - Professional Edition");
    setGeometry(100, 100, 800, 650);
    setStyleSheet("QMainWindow { background-color: #f0f0f0; }");
    
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    centralWidget->setStyleSheet(
        "#centralWidget { background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(16,42,67,230), stop:1 rgba(42,111,151,220)); }"
    );
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(24, 24, 24, 24);
    mainLayout->setSpacing(18);
    
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setStyleSheet("QScrollArea { background: transparent; }");
    
    stackedWidget = new QStackedWidget(this);
    stackedWidget->setStyleSheet("QStackedWidget { border-radius: 18px; background: transparent; }");
    
    scrollArea->setWidget(stackedWidget);
    mainLayout->addWidget(scrollArea);
    
    createMainMenu();
    createAdminPanel();
    createPatientPanel();
    createDoctorPanel();
    createLabPanel();
    createWardPanel();
    
    backButton = new QPushButton("← Back to Menu", this);
    backButton->setStyleSheet("QPushButton { padding: 8px; background-color: #2196F3; color: white; }");
    connect(backButton, &QPushButton::clicked, this, &MainWindow::goBack);
    backButton->hide();
    mainLayout->addWidget(backButton);
}

void MainWindow::createMainMenu()
{
    QWidget *menuPage = new QWidget();
    menuPage->setStyleSheet("background-color: rgba(255,255,255,0.90); border-radius: 24px;");
    QVBoxLayout *layout = new QVBoxLayout(menuPage);
    layout->setContentsMargins(28, 28, 28, 28);
    layout->setSpacing(20);
    
    QWidget *heroBanner = new QWidget();
    heroBanner->setStyleSheet("background: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #0b486b, stop:1 #2196F3); border-radius: 20px;");
    QHBoxLayout *heroLayout = new QHBoxLayout(heroBanner);
    heroLayout->setContentsMargins(18, 18, 18, 18);
    heroLayout->setSpacing(20);

    QLabel *logoLabel = new QLabel();
    logoLabel->setPixmap(createHospitalLogoPixmap());
    logoLabel->setFixedSize(120, 120);
    heroLayout->addWidget(logoLabel, 0, Qt::AlignVCenter);

    QVBoxLayout *heroText = new QVBoxLayout();
    QLabel *nameLabel = new QLabel("St. Mercy General Hospital");
    nameLabel->setStyleSheet("color: white; font-weight: 800;");
    QLabel *subtitleLabel = new QLabel("Compassion. Care. Cure.");
    subtitleLabel->setStyleSheet("color: #BBDEFB; margin-top: 6px;");
    heroText->addWidget(nameLabel);
    heroText->addWidget(subtitleLabel);
    heroText->addStretch();
    heroLayout->addLayout(heroText);

    heroLayout->addStretch();

    QWidget *zoomPanel = new QWidget();
    QHBoxLayout *zoomLayout = new QHBoxLayout(zoomPanel);
    zoomLayout->setSpacing(8);
    zoomLayout->setContentsMargins(0, 0, 0, 0);

    QPushButton *zoomOutBtn = new QPushButton("A-");
    QPushButton *zoomInBtn = new QPushButton("A+");
    zoomLabel = new QLabel();
    zoomLabel->setStyleSheet("color: #BBDEFB;");

    zoomOutBtn->setFixedSize(42, 34);
    zoomInBtn->setFixedSize(42, 34);
    zoomOutBtn->setStyleSheet("QPushButton { background: rgba(255,255,255,0.18); color: white; border-radius: 8px; } QPushButton:hover { background: rgba(255,255,255,0.28); }");
    zoomInBtn->setStyleSheet("QPushButton { background: rgba(255,255,255,0.18); color: white; border-radius: 8px; } QPushButton:hover { background: rgba(255,255,255,0.28); }");

    connect(zoomInBtn, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(zoomOutBtn, &QPushButton::clicked, this, &MainWindow::zoomOut);

    zoomLayout->addWidget(zoomLabel, 0, Qt::AlignVCenter);
    updateZoom();
    zoomLayout->addWidget(zoomOutBtn);
    zoomLayout->addWidget(zoomInBtn);
    heroLayout->addWidget(zoomPanel, 0, Qt::AlignVCenter);

    layout->addWidget(heroBanner);

    QLabel *titleLabel = new QLabel("🏥 HOSPITAL MANAGEMENT SYSTEM");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #102a43;");
    layout->addWidget(titleLabel);
    
    layout->addSpacing(10);
    
    QPushButton *adminBtn = new QPushButton("👔 Admin Panel");
    QPushButton *patientBtn = new QPushButton("🤒 Patient Menu");
    QPushButton *doctorBtn = new QPushButton("👨‍⚕️ Doctor Menu");
    QPushButton *labBtn = new QPushButton("🧪 Lab Test");
    QPushButton *wardBtn = new QPushButton("🛏️ Ward Admission");
    QPushButton *exitBtn = new QPushButton("❌ Exit");
    
    QString btnStyle = "QPushButton { padding: 15px; min-width: 250px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #1976D2, stop:1 #42A5F5); color: white; border-radius: 12px; font-weight: bold; } "
                       "QPushButton:hover { background-color: #1565C0; } "
                       "QPushButton:pressed { background-color: #0D47A1; }";
    adminBtn->setStyleSheet(btnStyle);
    patientBtn->setStyleSheet(btnStyle);
    doctorBtn->setStyleSheet(btnStyle);
    labBtn->setStyleSheet(btnStyle);
    wardBtn->setStyleSheet(btnStyle);
    exitBtn->setStyleSheet("QPushButton { padding: 15px; min-width: 250px; background-color: #f44336; "
                           "color: white; border-radius: 5px; font-weight: bold; }");
    
    connect(adminBtn, &QPushButton::clicked, this, &MainWindow::showAdminPanel);
    connect(patientBtn, &QPushButton::clicked, this, &MainWindow::showPatientMenu);
    connect(doctorBtn, &QPushButton::clicked, this, &MainWindow::showDoctorMenu);
    connect(labBtn, &QPushButton::clicked, this, &MainWindow::showLabTest);
    connect(wardBtn, &QPushButton::clicked, this, &MainWindow::showWardAdmission);
    connect(exitBtn, &QPushButton::clicked, this, &QWidget::close);
    
    layout->addStretch();
    layout->addWidget(adminBtn, 0, Qt::AlignCenter);
    layout->addWidget(patientBtn, 0, Qt::AlignCenter);
    layout->addWidget(doctorBtn, 0, Qt::AlignCenter);
    layout->addWidget(labBtn, 0, Qt::AlignCenter);
    layout->addWidget(wardBtn, 0, Qt::AlignCenter);
    layout->addWidget(exitBtn, 0, Qt::AlignCenter);
    layout->addStretch();

    QLabel *footerLabel = new QLabel("© Copyright owned @Lokesh @Anurag");
    footerLabel->setStyleSheet("color: #375a7f; font-size: 11px;");
    footerLabel->setAlignment(Qt::AlignRight);
    layout->addWidget(footerLabel);
    
    stackedWidget->addWidget(menuPage);
}

void MainWindow::createAdminPanel()
{
    QWidget *adminPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(adminPage);
    
    QLabel *title = new QLabel("👔 ADMIN PANEL");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    title->setStyleSheet("color: #1976D2;");
    layout->addWidget(title);
    
    adminPage->setStyleSheet("background-color: rgba(255,255,255,0.92); border-radius: 24px;");
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    QString btnStyle = "QPushButton { padding: 12px; min-width: 220px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #43A047, stop:1 #66BB6A); color: white; border-radius: 12px; } "
                       "QPushButton:hover { background-color: #388E3C; } "
                       "QPushButton:pressed { background-color: #2E7D32; }";
    
    QPushButton *hireBtn = new QPushButton("➕ Hire a Doctor");
    QPushButton *sackBtn = new QPushButton("➖ Sack a Doctor");
    QPushButton *wardBtn = new QPushButton("🏗️ Manage Wards");
    QPushButton *bedBtn = new QPushButton("🛏️ Manage Beds");
    QPushButton *doctorInfoBtn = new QPushButton("📋 View Doctors");
    QPushButton *patientInfoBtn = new QPushButton("📋 View Patients");
    QPushButton *incomeBtn = new QPushButton("💰 View Income");
    
    for (auto btn : {hireBtn, sackBtn, wardBtn, bedBtn, doctorInfoBtn, patientInfoBtn, incomeBtn}) {
        btn->setStyleSheet(btnStyle);
    }
    
    connect(hireBtn, &QPushButton::clicked, this, &MainWindow::onHireDoctor);
    connect(sackBtn, &QPushButton::clicked, this, &MainWindow::onSackDoctor);
    connect(wardBtn, &QPushButton::clicked, this, &MainWindow::onManageWards);
    connect(bedBtn, &QPushButton::clicked, this, &MainWindow::onManageBeds);
    connect(doctorInfoBtn, &QPushButton::clicked, this, &MainWindow::onViewDoctorInfo);
    connect(patientInfoBtn, &QPushButton::clicked, this, &MainWindow::onViewPatientInfo);
    connect(incomeBtn, &QPushButton::clicked, this, &MainWindow::onViewIncome);
    
    layout->addWidget(hireBtn);
    layout->addWidget(sackBtn);
    layout->addWidget(wardBtn);
    layout->addWidget(bedBtn);
    layout->addWidget(doctorInfoBtn);
    layout->addWidget(patientInfoBtn);
    layout->addWidget(incomeBtn);
    layout->addStretch();
    
    stackedWidget->addWidget(adminPage);
}

void MainWindow::createPatientPanel()
{
    QWidget *patientPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(patientPage);
    
    QLabel *title = new QLabel("🤒 PATIENT MENU");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    title->setStyleSheet("color: #1976D2;");
    layout->addWidget(title);
    
    patientPage->setStyleSheet("background-color: rgba(255,255,255,0.92); border-radius: 24px;");
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    QString btnStyle = "QPushButton { padding: 12px; min-width: 220px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #FB8C00, stop:1 #FFB74D); color: white; border-radius: 12px; } "
                       "QPushButton:hover { background-color: #F57C00; } "
                       "QPushButton:pressed { background-color: #EF6C00; }";
    
    QPushButton *registerBtn = new QPushButton("✏️ Register New Patient");
    QPushButton *viewBtn = new QPushButton("👁️ View All Patients");
    QPushButton *updateBtn = new QPushButton("🔄 Update Patient");
    
    for (auto btn : {registerBtn, viewBtn, updateBtn}) {
        btn->setStyleSheet(btnStyle);
    }
    
    connect(registerBtn, &QPushButton::clicked, this, &MainWindow::onRegisterPatient);
    connect(viewBtn, &QPushButton::clicked, this, &MainWindow::onViewPatients);
    connect(updateBtn, &QPushButton::clicked, this, &MainWindow::onUpdatePatient);
    
    layout->addWidget(registerBtn);
    layout->addWidget(viewBtn);
    layout->addWidget(updateBtn);
    layout->addStretch();
    
    stackedWidget->addWidget(patientPage);
}

void MainWindow::createDoctorPanel()
{
    QWidget *doctorPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(doctorPage);
    
    QLabel *title = new QLabel("👨‍⚕️ DOCTOR MENU");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    title->setStyleSheet("color: #1976D2;");
    layout->addWidget(title);
    
    doctorPage->setStyleSheet("background-color: rgba(255,255,255,0.92); border-radius: 24px;");
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    QString btnStyle = "QPushButton { padding: 12px; min-width: 220px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #8E24AA, stop:1 #AB47BC); color: white; border-radius: 12px; } "
                       "QPushButton:hover { background-color: #7B1FA2; } "
                       "QPushButton:pressed { background-color: #6A1B9A; }";
    
    QPushButton *viewBtn = new QPushButton("👁️ View All Doctors");
    QPushButton *patientsBtn = new QPushButton("👥 Assigned Patients");
    QPushButton *scheduleBtn = new QPushButton("📅 View Schedule");
    
    for (auto btn : {viewBtn, patientsBtn, scheduleBtn}) {
        btn->setStyleSheet(btnStyle);
    }
    
    connect(viewBtn, &QPushButton::clicked, this, &MainWindow::onViewDoctors);
    connect(patientsBtn, &QPushButton::clicked, this, &MainWindow::onViewAssignedPatients);
    connect(scheduleBtn, &QPushButton::clicked, this, &MainWindow::onViewSchedule);
    
    layout->addWidget(viewBtn);
    layout->addWidget(patientsBtn);
    layout->addWidget(scheduleBtn);
    layout->addStretch();
    
    stackedWidget->addWidget(doctorPage);
}

void MainWindow::createLabPanel()
{
    QWidget *labPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(labPage);
    
    QLabel *title = new QLabel("🧪 LAB TEST MANAGEMENT");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    title->setStyleSheet("color: #1976D2;");
    layout->addWidget(title);
    
    labPage->setStyleSheet("background-color: rgba(255,255,255,0.92); border-radius: 24px;");
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    QString btnStyle = "QPushButton { padding: 12px; min-width: 220px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #00838F, stop:1 #26C6DA); color: white; border-radius: 12px; } "
                       "QPushButton:hover { background-color: #006064; } "
                       "QPushButton:pressed { background-color: #004D40; }";
    
    QPushButton *scheduleBtn = new QPushButton("📝 Schedule Lab Test");
    QPushButton *viewBtn = new QPushButton("👁️ View Test Results");
    QPushButton *historyBtn = new QPushButton("📊 Test History");
    
    for (auto btn : {scheduleBtn, viewBtn, historyBtn}) {
        btn->setStyleSheet(btnStyle);
    }
    
    connect(scheduleBtn, &QPushButton::clicked, this, &MainWindow::onScheduleLabTest);
    connect(viewBtn, &QPushButton::clicked, this, &MainWindow::onViewLabResults);
    connect(historyBtn, &QPushButton::clicked, this, &MainWindow::onViewTestHistory);
    
    layout->addWidget(scheduleBtn);
    layout->addWidget(viewBtn);
    layout->addWidget(historyBtn);
    layout->addStretch();
    
    stackedWidget->addWidget(labPage);
}

void MainWindow::createWardPanel()
{
    QWidget *wardPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(wardPage);
    
    QLabel *title = new QLabel("🛏️ WARD ADMISSION");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    title->setStyleSheet("color: #1976D2;");
    layout->addWidget(title);
    
    wardPage->setStyleSheet("background-color: rgba(255,255,255,0.92); border-radius: 24px;");
    layout->setContentsMargins(24, 24, 24, 24);
    layout->setSpacing(16);
    QString btnStyle = "QPushButton { padding: 12px; min-width: 220px; background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #C2185B, stop:1 #E91E63); color: white; border-radius: 12px; } "
                       "QPushButton:hover { background-color: #AD1457; } "
                       "QPushButton:pressed { background-color: #880E4F; }";
    
    QPushButton *admitBtn = new QPushButton("➕ Admit Patient");
    QPushButton *dischargeBtn = new QPushButton("❌ Discharge Patient");
    QPushButton *availabilityBtn = new QPushButton("📊 Ward Status");
    
    for (auto btn : {admitBtn, dischargeBtn, availabilityBtn}) {
        btn->setStyleSheet(btnStyle);
    }
    
    connect(admitBtn, &QPushButton::clicked, this, &MainWindow::onAdmitPatient);
    connect(dischargeBtn, &QPushButton::clicked, this, &MainWindow::onDischargePatient);
    connect(availabilityBtn, &QPushButton::clicked, this, &MainWindow::onCheckWardAvailability);
    
    layout->addWidget(admitBtn);
    layout->addWidget(dischargeBtn);
    layout->addWidget(availabilityBtn);
    layout->addStretch();
    
    stackedWidget->addWidget(wardPage);
}

// ============ ADMIN PANEL IMPLEMENTATION ============
void MainWindow::onHireDoctor()
{
    DoctorHiringDialog dialog(this);
    QString name, id, specialization, degree, dept;
    
    if (dialog.getDoctorData(name, id, specialization, degree, dept)) {
        Database::getInstance().addDoctor(name, id, specialization, degree, dept);
        QMessageBox::information(this, "Success", "Doctor hired successfully!\n\n"
                                "Name: " + name + "\nID: " + id + "\nSpecialization: " + specialization);
    }
}

void MainWindow::onSackDoctor()
{
    bool ok;
    QString docId = QInputDialog::getText(this, "Remove Doctor", "Enter Doctor ID:", 
                                         QLineEdit::Normal, "", &ok);
    if (ok && !docId.isEmpty()) {
        Database& db = Database::getInstance();
        Doctor doc = db.getDoctorById(docId);
        if (!doc.id.isEmpty()) {
            db.removeDoctor(docId);
            QMessageBox::information(this, "Success", "Doctor removed successfully!\n\n"
                                    "Doctor: " + doc.name);
        } else {
            QMessageBox::warning(this, "Error", "Doctor not found!");
        }
    }
}

void MainWindow::onManageWards()
{
    QMessageBox::information(this, "Ward Management", 
                            "Ward Management Options:\n\n"
                            "• General Ward - 10 beds\n"
                            "• Private Ward - 5 beds\n"
                            "• ICU Ward - 6 beds\n"
                            "• Semi-Private - 4 beds\n\n"
                            "Total: 25 beds");
}

void MainWindow::onManageBeds()
{
    QMessageBox::information(this, "Bed Management", 
                            "Current Bed Status:\n\n"
                            "General Ward: 10 beds (8 occupied)\n"
                            "Private Ward: 5 beds (4 occupied)\n"
                            "ICU: 6 beds (5 occupied)\n"
                            "Semi-Private: 4 beds (2 occupied)\n\n"
                            "Total Beds: 25\nOccupied: 19\nAvailable: 6");
}

void MainWindow::onViewDoctorInfo()
{
    SearchDialog dialog("All Doctors", {"ID", "Name", "Specialization", "Department", "Join Date"}, this);
    
    Database& db = Database::getInstance();
    QVector<Doctor> doctors = db.getAllDoctors();
    
    if (doctors.isEmpty()) {
        QMessageBox::information(this, "Doctors List", "No doctors registered yet!");
        return;
    }
    
    for (const auto &doc : doctors) {
        dialog.addRow({doc.id, doc.name, doc.specialization, doc.department, doc.joinDate});
    }
    
    dialog.exec();
}

void MainWindow::onViewPatientInfo()
{
    SearchDialog dialog("All Patients", {"ID", "Name", "Age", "Gender", "Phone", "Blood Group"}, this);
    
    Database& db = Database::getInstance();
    QVector<Patient> patients = db.getAllPatients();
    
    if (patients.isEmpty()) {
        QMessageBox::information(this, "Patients List", "No patients registered yet!");
        return;
    }
    
    for (const auto &patient : patients) {
        dialog.addRow({patient.id, patient.name, QString::number(patient.age), 
                      patient.gender, patient.phone, patient.bloodGroup});
    }
    
    dialog.exec();
}

void MainWindow::onViewIncome()
{
    int income = Database::getInstance().getTotalIncome();
    QMessageBox::information(this, "Hospital Income Report", 
                            "💰 REVENUE REPORT\n\n"
                            "Total Hospital Income: " + QString::number(income) + " PKR\n\n"
                            "Income Breakdown:\n"
                            "• Doctor Hiring: 50,000 PKR each\n"
                            "• Patient Registration: 5,000 PKR each\n"
                            "• Lab Tests: 1,000 - 5,000 PKR\n"
                            "• Ward Admission: 5,000 - 10,000 PKR");
}

// ============ PATIENT PANEL IMPLEMENTATION ============
void MainWindow::onRegisterPatient()
{
    PatientRegistrationDialog dialog(this);
    QString name, id, age, gender, phone, bloodGroup, address;
    
    if (dialog.getPatientData(name, id, age, gender, phone, bloodGroup, address)) {
        Database::getInstance().addPatient(name, id, age, gender, phone, bloodGroup, address);
        QMessageBox::information(this, "Success", "Patient registered successfully!\n\n"
                                "Name: " + name + "\nID: " + id + "\nAge: " + age + 
                                "\nBlood Group: " + bloodGroup);
    }
}

void MainWindow::onViewPatients()
{
    SearchDialog dialog("All Registered Patients", {"ID", "Name", "Age", "Gender", "Phone", "Blood Group", "Registration Date"}, this);
    
    Database& db = Database::getInstance();
    QVector<Patient> patients = db.getAllPatients();
    
    if (patients.isEmpty()) {
        QMessageBox::information(this, "Patients List", "No patients registered yet!");
        return;
    }
    
    for (const auto &patient : patients) {
        dialog.addRow({patient.id, patient.name, QString::number(patient.age), 
                      patient.gender, patient.phone, patient.bloodGroup, patient.registrationDate});
    }
    
    dialog.exec();
}

void MainWindow::onUpdatePatient()
{
    bool ok;
    QString patientId = QInputDialog::getText(this, "Update Patient", "Enter Patient ID:", 
                                             QLineEdit::Normal, "", &ok);
    if (ok && !patientId.isEmpty()) {
        Database& db = Database::getInstance();
        Patient patient = db.getPatientById(patientId);
        if (patient.id.isEmpty()) {
            QMessageBox::warning(this, "Error", "Patient not found!");
            return;
        }
        
        QMessageBox::information(this, "Patient Details", 
                                "Patient: " + patient.name + "\n"
                                "Age: " + QString::number(patient.age) + "\n"
                                "Gender: " + patient.gender + "\n"
                                "Phone: " + patient.phone + "\n"
                                "Blood Group: " + patient.bloodGroup + "\n"
                                "Address: " + patient.address);
    }
}

// ============ DOCTOR PANEL IMPLEMENTATION ============
void MainWindow::onViewDoctors()
{
    SearchDialog dialog("All Registered Doctors", {"ID", "Name", "Specialization", "Degree", "Department"}, this);
    
    Database& db = Database::getInstance();
    QVector<Doctor> doctors = db.getAllDoctors();
    
    if (doctors.isEmpty()) {
        QMessageBox::information(this, "Doctors List", "No doctors registered yet!");
        return;
    }
    
    for (const auto &doc : doctors) {
        dialog.addRow({doc.id, doc.name, doc.specialization, doc.degree, doc.department});
    }
    
    dialog.exec();
}

void MainWindow::onViewAssignedPatients()
{
    bool ok;
    QString docId = QInputDialog::getText(this, "View Patients", "Enter Doctor ID:", 
                                         QLineEdit::Normal, "", &ok);
    if (ok && !docId.isEmpty()) {
        QMessageBox::information(this, "Assigned Patients", 
                                "Doctor ID: " + docId + "\n\n"
                                "Patients under this doctor's care will be displayed here.");
    }
}

void MainWindow::onViewSchedule()
{
    QMessageBox::information(this, "Doctor Schedule", 
                            "📅 WEEKLY SCHEDULE\n\n"
                            "Monday - Friday: 9:00 AM - 5:00 PM\n"
                            "Saturday: 9:00 AM - 1:00 PM\n"
                            "Sunday: OFF\n\n"
                            "Appointment Slots Available:\n"
                            "• 9:00 - 10:00 AM\n"
                            "• 10:00 - 11:00 AM\n"
                            "• 2:00 - 3:00 PM\n"
                            "• 3:00 - 4:00 PM");
}

// ============ LAB PANEL IMPLEMENTATION ============
void MainWindow::onScheduleLabTest()
{
    LabTestDialog dialog(this);
    QString patientId, testType, date;
    
    if (dialog.getTestData(patientId, testType, date)) {
        Database::getInstance().addLabTest(patientId, testType, date);
        QMessageBox::information(this, "Success", "Lab test scheduled successfully!\n\n"
                                "Patient ID: " + patientId + "\nTest: " + testType + 
                                "\nDate: " + date);
    }
}

void MainWindow::onViewLabResults()
{
    bool ok;
    QString patientId = QInputDialog::getText(this, "View Results", "Enter Patient ID:", 
                                             QLineEdit::Normal, "", &ok);
    if (ok && !patientId.isEmpty()) {
        SearchDialog dialog("Lab Test Results", {"Patient ID", "Test Type", "Test Date", "Result"}, this);
        
        Database& db = Database::getInstance();
        QVector<LabTest> tests = db.getLabTestsByPatient(patientId);
        
        if (tests.isEmpty()) {
            QMessageBox::information(this, "Results", "No lab tests found for this patient!");
            return;
        }
        
        for (const auto &test : tests) {
            dialog.addRow({test.patientId, test.testType, test.testDate, test.result});
        }
        
        dialog.exec();
    }
}

void MainWindow::onViewTestHistory()
{
    bool ok;
    QString patientId = QInputDialog::getText(this, "Test History", "Enter Patient ID:", 
                                             QLineEdit::Normal, "", &ok);
    if (ok && !patientId.isEmpty()) {
        SearchDialog dialog("Complete Test History", {"Patient ID", "Test Type", "Date"}, this);
        
        Database& db = Database::getInstance();
        QVector<LabTest> tests = db.getLabTestsByPatient(patientId);
        
        if (tests.isEmpty()) {
            QMessageBox::information(this, "History", "No test history for this patient!");
            return;
        }
        
        for (const auto &test : tests) {
            dialog.addRow({test.patientId, test.testType, test.testDate});
        }
        
        dialog.exec();
    }
}

// ============ WARD PANEL IMPLEMENTATION ============
void MainWindow::onAdmitPatient()
{
    WardAdmissionDialog dialog(this);
    QString patientId, wardType, bedNo, docId;
    
    if (dialog.getAdmissionData(patientId, wardType, bedNo, docId)) {
        Database::getInstance().admitPatient(patientId, wardType, bedNo.toInt(), docId);
        QMessageBox::information(this, "Success", "Patient admitted successfully!\n\n"
                                "Patient ID: " + patientId + "\nWard: " + wardType + 
                                "\nBed #" + bedNo);
    }
}

void MainWindow::onDischargePatient()
{
    bool ok;
    QString patientId = QInputDialog::getText(this, "Discharge Patient", "Enter Patient ID:", 
                                             QLineEdit::Normal, "", &ok);
    if (ok && !patientId.isEmpty()) {
        Database::getInstance().dischargePatient(patientId);
        QMessageBox::information(this, "Success", "Patient discharged successfully!\n\n"
                                "Patient ID: " + patientId + "\nDischarge Date: " + 
                                QDate::currentDate().toString("dd/MM/yyyy"));
    }
}

void MainWindow::onCheckWardAvailability()
{
    QVector<Admission> admissions = Database::getInstance().getActiveAdmissions();
    
    int generalOccupied = 0, privateOccupied = 0, icuOccupied = 0;
    for (const auto &adm : admissions) {
        if (adm.wardType == "General Ward") generalOccupied++;
        else if (adm.wardType == "Private Ward") privateOccupied++;
        else if (adm.wardType == "ICU") icuOccupied++;
    }
    
    QString status = QString(
        "🛏️ WARD AVAILABILITY STATUS\n\n"
        "General Ward: %1/10 occupied (%2 available)\n"
        "Private Ward: %3/5 occupied (%4 available)\n"
        "ICU: %5/6 occupied (%6 available)\n\n"
        "Total Occupancy: %7/21 beds (33%)"
    ).arg(generalOccupied).arg(10-generalOccupied)
     .arg(privateOccupied).arg(5-privateOccupied)
     .arg(icuOccupied).arg(6-icuOccupied)
     .arg(admissions.size());
    
    QMessageBox::information(this, "Ward Status", status);
}

// ============ NAVIGATION ============
void MainWindow::showAdminPanel()
{
    backButton->show();
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showPatientMenu()
{
    backButton->show();
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::showDoctorMenu()
{
    backButton->show();
    stackedWidget->setCurrentIndex(3);
}

void MainWindow::showLabTest()
{
    backButton->show();
    stackedWidget->setCurrentIndex(4);
}

void MainWindow::showWardAdmission()
{
    backButton->show();
    stackedWidget->setCurrentIndex(5);
}

void MainWindow::zoomIn()
{
    if (zoomFactor < 2.0) {
        zoomFactor += 0.1;
        updateZoom();
    }
}

void MainWindow::zoomOut()
{
    if (zoomFactor > 0.7) {
        zoomFactor -= 0.1;
        updateZoom();
    }
}

void MainWindow::updateZoom()
{
    QFont zoomFont = qApp->font();
    zoomFont.setPointSizeF(baseFontSize * zoomFactor);
    qApp->setFont(zoomFont);
    applyZoomToWidget(this, zoomFont);

    if (zoomLabel) {
        zoomLabel->setText(QString("Zoom: %1%") .arg(int(zoomFactor * 100)));
    }
}

void MainWindow::applyZoomToWidget(QWidget *widget, const QFont &font)
{
    if (!widget) {
        return;
    }
    widget->setFont(font);
    for (QObject *child : widget->children()) {
        if (QWidget *childWidget = qobject_cast<QWidget *>(child)) {
            applyZoomToWidget(childWidget, font);
        }
    }
}

void MainWindow::goBack()
{
    backButton->hide();
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    Database::getInstance().saveData();
    event->accept();
}
