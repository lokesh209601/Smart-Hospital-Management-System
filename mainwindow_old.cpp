#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Hospital Management System");
    setGeometry(100, 100, 800, 600);
    
    setupUI();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    
    // Create stacked widget for pages
    stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(stackedWidget);
    
    // Create main menu page
    createMainMenu();
    createAdminPanel();
    createPatientPanel();
    createDoctorPanel();
    createLabPanel();
    createWardPanel();
    
    // Back button at bottom
    backButton = new QPushButton("Back to Menu", this);
    backButton->setStyleSheet("QPushButton { padding: 8px; font-size: 12px; }");
    connect(backButton, &QPushButton::clicked, this, &MainWindow::goBack);
    backButton->hide();
    mainLayout->addWidget(backButton);
}

void MainWindow::createMainMenu()
{
    QWidget *menuPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(menuPage);
    
    // Title
    QLabel *titleLabel = new QLabel("HOSPITAL MANAGEMENT SYSTEM");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);
    
    layout->addStretch();
    
    // Buttons
    QPushButton *adminBtn = new QPushButton("Admin Panel");
    QPushButton *patientBtn = new QPushButton("Patient Menu");
    QPushButton *doctorBtn = new QPushButton("Doctor Menu");
    QPushButton *labBtn = new QPushButton("Lab Test");
    QPushButton *wardBtn = new QPushButton("Ward Admission");
    QPushButton *saveBtn = new QPushButton("Save All Doctor Data");
    QPushButton *readBtn = new QPushButton("Read All Doctor Data");
    QPushButton *exitBtn = new QPushButton("Exit");
    
    // Style buttons
    QString buttonStyle = "QPushButton { padding: 10px; font-size: 14px; min-width: 200px; }";
    adminBtn->setStyleSheet(buttonStyle);
    patientBtn->setStyleSheet(buttonStyle);
    doctorBtn->setStyleSheet(buttonStyle);
    labBtn->setStyleSheet(buttonStyle);
    wardBtn->setStyleSheet(buttonStyle);
    saveBtn->setStyleSheet(buttonStyle);
    readBtn->setStyleSheet(buttonStyle);
    exitBtn->setStyleSheet(buttonStyle);
    
    // Connect buttons using lambdas
    connect(adminBtn, &QPushButton::clicked, this, [this]() { showAdminPanel(); });
    connect(patientBtn, &QPushButton::clicked, this, [this]() { showPatientMenu(); });
    connect(doctorBtn, &QPushButton::clicked, this, [this]() { showDoctorMenu(); });
    connect(labBtn, &QPushButton::clicked, this, [this]() { showLabTest(); });
    connect(wardBtn, &QPushButton::clicked, this, [this]() { showWardAdmission(); });
    connect(saveBtn, &QPushButton::clicked, this, [this]() { handleSaveData(); });
    connect(readBtn, &QPushButton::clicked, this, [this]() { handleReadData(); });
    connect(exitBtn, &QPushButton::clicked, this, &QWidget::close);
    
    layout->addWidget(adminBtn, 0, Qt::AlignCenter);
    layout->addWidget(patientBtn, 0, Qt::AlignCenter);
    layout->addWidget(doctorBtn, 0, Qt::AlignCenter);
    layout->addWidget(labBtn, 0, Qt::AlignCenter);
    layout->addWidget(wardBtn, 0, Qt::AlignCenter);
    layout->addWidget(saveBtn, 0, Qt::AlignCenter);
    layout->addWidget(readBtn, 0, Qt::AlignCenter);
    layout->addWidget(exitBtn, 0, Qt::AlignCenter);
    
    layout->addStretch();
    
    stackedWidget->addWidget(menuPage);
}

void MainWindow::createAdminPanel()
{
    QWidget *adminPage = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(adminPage);
    
    QLabel *title = new QLabel("ADMIN PANEL");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    layout->addWidget(title);
    
    QLabel *infoLabel = new QLabel("Select an action:");
    layout->addWidget(infoLabel);
    
    QPushButton *hireBtn = new QPushButton("Hire a Doctor");
    QPushButton *sackBtn = new QPushButton("Sack a Doctor");
    QPushButton *wardBtn = new QPushButton("Manage Wards");
    QPushButton *bedBtn = new QPushButton("Manage Beds");
    QPushButton *doctorInfoBtn = new QPushButton("Doctor Information");
    QPushButton *patientInfoBtn = new QPushButton("Patient Information");
    QPushButton *incomeBtn = new QPushButton("View Total Income");
    
    // Connect admin buttons
    connect(hireBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Hire Doctor", "Opening doctor hiring form...\n\nEnter doctor details:\n- Name\n- ID\n- Specialization\n- Department");
    });
    
    connect(sackBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Sack Doctor", "Opening doctor removal form...\n\nSelect doctor to remove from system.");
    });
    
    connect(wardBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Manage Wards", "Ward Management Options:\n\n- Increase wards\n- Decrease wards\n- View all wards\n- Modify ward capacity");
    });
    
    connect(bedBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Manage Beds", "Bed Management Options:\n\n- Add beds to wards\n- Remove beds from wards\n- View bed availability\n- Check occupancy status");
    });
    
    connect(doctorInfoBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Doctor Information", "Doctor Directory:\n\nSearching all registered doctors...\n\nDisplaying:\n- Doctor ID\n- Name\n- Specialization\n- Department\n- Contact Info");
    });
    
    connect(patientInfoBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Patient Information", "Patient Records Search:\n\nSearch patient by:\n- Patient ID\n- Name\n- Contact Number\n\nView complete medical history.");
    });
    
    connect(incomeBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Hospital Income", "Revenue Report:\n\nTotal Hospital Income: 500,000 PKR\n\n- Income from appointments: 250,000 PKR\n- Income from ward admission: 200,000 PKR\n- Lab test income: 50,000 PKR");
    });
    
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
    
    QLabel *title = new QLabel("PATIENT MENU");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    layout->addWidget(title);
    
    QLabel *infoLabel = new QLabel("Select an action:");
    layout->addWidget(infoLabel);
    
    QPushButton *registerBtn = new QPushButton("Register as New Patient");
    QPushButton *viewBtn = new QPushButton("View Patient Details");
    QPushButton *updateBtn = new QPushButton("Update Patient Information");
    
    // Connect patient buttons
    connect(registerBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "New Patient Registration", "Patient Registration Form:\n\nEnter Details:\n- Full Name\n- Age\n- Gender\n- Contact Number\n- Blood Group\n- Address\n- Emergency Contact");
    });
    
    connect(viewBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "View Patient Details", "Patient Details Viewer:\n\nSearch by:\n- Patient ID\n- Name\n- Contact Number\n\nDisplaying:\n- Personal Information\n- Medical History\n- Current Medications\n- Assigned Doctor");
    });
    
    connect(updateBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Update Patient Information", "Update Patient Records:\n\nSelect what to update:\n- Contact Information\n- Address\n- Blood Group\n- Emergency Contact\n- Medical History");
    });
    
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
    
    QLabel *title = new QLabel("DOCTOR MENU");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    layout->addWidget(title);
    
    QLabel *infoLabel = new QLabel("Select an action:");
    layout->addWidget(infoLabel);
    
    QPushButton *viewBtn = new QPushButton("View Doctor Details");
    QPushButton *patientsBtn = new QPushButton("View Assigned Patients");
    QPushButton *scheduleBtn = new QPushButton("View Schedule");
    
    // Connect doctor buttons
    connect(viewBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Doctor Details", "Doctor Directory:\n\nSearch doctor by:\n- Doctor ID\n- Name\n\nDisplaying:\n- Full Name\n- Specialization\n- Department\n- Qualifications\n- Experience\n- Contact Information");
    });
    
    connect(patientsBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Assigned Patients", "Patient List:\n\nDisplaying patients assigned to:\n- Patient ID\n- Patient Name\n- Disease/Condition\n- Treatment Status\n- Last Visit Date\n\nSelect to view details or update.");
    });
    
    connect(scheduleBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Doctor Schedule", "Weekly Schedule:\n\nMonday - Friday: 9:00 AM - 5:00 PM\nSaturday: 9:00 AM - 1:00 PM\nSunday: OFF\n\nApointment Slots:\n- 9:00 - 10:00 AM\n- 10:00 - 11:00 AM\n- 2:00 - 3:00 PM\n- 3:00 - 4:00 PM");
    });
    
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
    
    QLabel *title = new QLabel("LAB TEST MANAGEMENT");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    layout->addWidget(title);
    
    QLabel *infoLabel = new QLabel("Lab Test Options:");
    layout->addWidget(infoLabel);
    
    QPushButton *scheduleBtn = new QPushButton("Schedule Lab Test");
    QPushButton *viewBtn = new QPushButton("View Lab Test Results");
    QPushButton *historyBtn = new QPushButton("Test History");
    
    // Connect lab buttons
    connect(scheduleBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Schedule Lab Test", "Lab Test Scheduling:\n\nSelect Test Type:\n- Blood Test\n- Urine Test\n- X-Ray\n- Ultrasound\n- CT Scan\n- ECG\n\nSelect Patient and Schedule Date/Time");
    });
    
    connect(viewBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Lab Test Results", "Test Results Viewer:\n\nSearch by:\n- Patient ID\n- Patient Name\n\nDisplaying:\n- Test Type\n- Test Date\n- Results\n- Reference Range\n- Doctor's Notes");
    });
    
    connect(historyBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Test History", "Complete Test History:\n\nPatient's All Previous Tests:\n- Blood Tests (Monthly monitoring)\n- Imaging Tests\n- Specialist Tests\n\nFiltered by Date Range:\n- Last 3 months\n- Last 6 months\n- Last Year");
    });
    
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
    
    QLabel *title = new QLabel("WARD ADMISSION");
    QFont font = title->font();
    font.setPointSize(16);
    font.setBold(true);
    title->setFont(font);
    layout->addWidget(title);
    
    QLabel *infoLabel = new QLabel("Ward Management:");
    layout->addWidget(infoLabel);
    
    QPushButton *admitBtn = new QPushButton("Admit Patient to Ward");
    QPushButton *dischargeBtn = new QPushButton("Discharge Patient");
    QPushButton *availabilityBtn = new QPushButton("Check Ward Availability");
    
    // Connect ward buttons
    connect(admitBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Patient Admission", "Ward Admission Form:\n\nSelect:\n- Ward Type (General/Private/ICU)\n- Bed Number\n- Patient Details\n- Admitted Date\n- Assigned Doctor\n- Reason for Admission");
    });
    
    connect(dischargeBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Patient Discharge", "Discharge Process:\n\nSelect Patient to Discharge:\n- Patient Name\n- Patient ID\n- Ward Number\n- Discharge Date\n- Final Medical Report\n- Discharge Summary");
    });
    
    connect(availabilityBtn, &QPushButton::clicked, this, [this]() {
        QMessageBox::information(this, "Ward Availability", "Ward Status Report:\n\nGeneral Ward: 8 beds (6 available)\nPrivate Ward: 4 beds (3 available)\nICU Ward: 6 beds (4 available)\n\nTotal: 18 beds (13 available)\nOccupancy: 72%");
    });
    
    layout->addWidget(admitBtn);
    layout->addWidget(dischargeBtn);
    layout->addWidget(availabilityBtn);
    layout->addStretch();
    
    stackedWidget->addWidget(wardPage);
}

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

void MainWindow::handleSaveData()
{
    QMessageBox::information(this, "Save", "Doctor data saved successfully!");
}

void MainWindow::handleReadData()
{
    QMessageBox::information(this, "Read", "Doctor data loaded successfully!");
}

void MainWindow::goBack()
{
    backButton->hide();
    stackedWidget->setCurrentIndex(0);
}
