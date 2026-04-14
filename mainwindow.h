#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();
    void createMainMenu();
    void createAdminPanel();
    void createPatientPanel();
    void createDoctorPanel();
    void createLabPanel();
    void createWardPanel();
    
    // Admin Panel Slots
    void onHireDoctor();
    void onSackDoctor();
    void onManageWards();
    void onManageBeds();
    void onViewDoctorInfo();
    void onViewPatientInfo();
    void onViewIncome();
    
    // Patient Panel Slots
    void onRegisterPatient();
    void onViewPatients();
    void onUpdatePatient();
    
    // Doctor Panel Slots
    void onViewDoctors();
    void onViewAssignedPatients();
    void onViewSchedule();
    
    // Lab Panel Slots
    void onScheduleLabTest();
    void onViewLabResults();
    void onViewTestHistory();
    
    // Ward Panel Slots
    void onAdmitPatient();
    void onDischargePatient();
    void onCheckWardAvailability();
    
    // Navigation Slots
    void showAdminPanel();
    void showPatientMenu();
    void showDoctorMenu();
    void showLabTest();
    void showWardAdmission();
    void goBack();

    // Zoom Controls
    void zoomIn();
    void zoomOut();
    void updateZoom();
    void applyZoomToWidget(QWidget *widget, const QFont &font);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    QStackedWidget *stackedWidget;
    QPushButton *backButton;
    QLabel *zoomLabel;
    double zoomFactor;
    double baseFontSize;
};

#endif // MAINWINDOW_H
