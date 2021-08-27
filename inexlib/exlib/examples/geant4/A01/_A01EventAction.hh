#ifndef A01EventAction_hh
#define A01EventAction_hh

#include <G4UserEventAction.hh>

#include "A01/HodoscopeHit.hh"
#include "A01/DriftChamberHit.hh"
#include "A01/EmCalorimeterHit.hh"
#include "A01/HadCalorimeterHit.hh"

#include <G4SDManager.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4Event.hh>

#include <inlib/histo/h1d>
#include <inlib/histo/c2d>

namespace A01 {

class EventAction : public G4UserEventAction {
public:
  virtual void BeginOfEventAction(const G4Event*) {}

  virtual void EndOfEventAction(const G4Event* evt) {
    G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
    HodoscopeHitsCollection* HHC1 = 0;
    HodoscopeHitsCollection* HHC2 = 0;
    DriftChamberHitsCollection* DHC1 = 0;
    DriftChamberHitsCollection* DHC2 = 0;
    EmCalorimeterHitsCollection* ECHC = 0;
    HadCalorimeterHitsCollection* HCHC = 0;
    if(HCE) {
      G4SDManager* SDman = G4SDManager::GetSDMpointer();
      G4int HHC1ID = SDman->GetCollectionID("hodoscope1/hodoscopeColl");
      G4int HHC2ID = SDman->GetCollectionID("hodoscope2/hodoscopeColl");
      G4int DHC1ID = SDman->GetCollectionID("chamber1/driftChamberColl");
      G4int DHC2ID = SDman->GetCollectionID("chamber2/driftChamberColl");
      G4int ECHCID = SDman->GetCollectionID("EMcalorimeter/EMcalorimeterColl");
      G4int HCHCID = SDman->GetCollectionID("HadCalorimeter/HadCalorimeterColl");

      HHC1 = (HodoscopeHitsCollection*)(HCE->GetHC(HHC1ID));
      HHC2 = (HodoscopeHitsCollection*)(HCE->GetHC(HHC2ID));
      DHC1 = (DriftChamberHitsCollection*)(HCE->GetHC(DHC1ID));
      DHC2 = (DriftChamberHitsCollection*)(HCE->GetHC(DHC2ID));
      ECHC = (EmCalorimeterHitsCollection*)(HCE->GetHC(ECHCID));
      HCHC = (HadCalorimeterHitsCollection*)(HCE->GetHC(HCHCID));
    }

    m_build_plots = false;
    bool dc1XY_cnv = m_dc1XY->is_converted();
    bool dc2XY_cnv = m_dc2XY->is_converted();
    bool evstof_cnv = m_evstof->is_converted();
    if(DHC1 && m_dc1Hits){
      int n_hit = DHC1->entries();
      m_dc1Hits->fill(n_hit);
      for(int i1=0;i1<n_hit;i1++){
        DriftChamberHit* aHit = (*DHC1)[i1];
        if(aHit) {
          G4ThreeVector localPos = aHit->GetLocalPos();
          if (m_dc1XY) m_dc1XY->fill(localPos.x(), localPos.y());
        }
      }
    }
    if(DHC2 && m_dc2Hits) {
      int n_hit = DHC2->entries();
      m_dc2Hits->fill(n_hit);
      for(int i1=0;i1<n_hit;i1++){
        DriftChamberHit* aHit = (*DHC2)[i1];
        if(aHit) {
          G4ThreeVector localPos = aHit->GetLocalPos();
          if (m_dc2XY) m_dc2XY->fill(localPos.x(), localPos.y());
        }
      }
    }
    if(ECHC) {
      int iHit = 0;
      double totalE = 0.;
      for(int i1=0;i1<80;i1++){
        EmCalorimeterHit* aHit = (*ECHC)[i1];
        if(aHit) {
          double eDep = aHit->GetEdep();
          if(eDep>0.){
            iHit++;
            totalE += eDep;
          }
        }
      }
      if (HHC1 && HHC2 && (HHC1->entries()==1) && (HHC2->entries()==1) ) {
        HodoscopeHit* aHit1 = (*HHC1)[0];
        HodoscopeHit* aHit2 = (*HHC2)[0];
        if(aHit1 && aHit2) {
          double tof = aHit2->GetTime() - aHit1->GetTime();
          if (m_evstof) m_evstof->fill(tof,totalE);
        }
      }
    }
    if(dc1XY_cnv!=m_dc1XY->is_converted()) m_build_plots = true;
    if(dc2XY_cnv!=m_dc2XY->is_converted()) m_build_plots = true;
    if(evstof_cnv!=m_evstof->is_converted()) m_build_plots = true;

    // Diagnostics

    if (verboseLevel==0 || evt->GetEventID() % verboseLevel != 0) return;

    G4PrimaryParticle* primary = evt->GetPrimaryVertex(0)->GetPrimary(0);
    G4cout << G4endl
           << ">>> Event " << evt->GetEventID() << " >>> Simulation truth : "
           << primary->GetG4code()->GetParticleName()
           << " " << primary->GetMomentum() << G4endl;

    if(HHC1) {
      int n_hit = HHC1->entries();
      G4cout << "Hodoscope 1 has " << n_hit << " hits." << G4endl;
      for(int i1=0;i1<n_hit;i1++)
      {
        HodoscopeHit* aHit = (*HHC1)[i1];
        aHit->Print();
      }
    }

    if(HHC2) {
      int n_hit = HHC2->entries();
      G4cout << "Hodoscope 2 has " << n_hit << " hits." << G4endl;
      for(int i1=0;i1<n_hit;i1++) {
        HodoscopeHit* aHit = (*HHC2)[i1];
        aHit->Print();
      }
    }

    if(DHC1) {
      int n_hit = DHC1->entries();
      G4cout << "Drift Chamber 1 has " << n_hit << " hits." << G4endl;
      for(int i2=0;i2<5;i2++) {
        for(int i1=0;i1<n_hit;i1++) {
          DriftChamberHit* aHit = (*DHC1)[i1];
          if(aHit->GetLayerID()==i2) aHit->Print();
        }
      }
    }

    if(DHC2) {
      int n_hit = DHC2->entries();
      G4cout << "Drift Chamber 2 has " << n_hit << " hits." << G4endl;
      for(int i2=0;i2<5;i2++) {
        for(int i1=0;i1<n_hit;i1++) {
          DriftChamberHit* aHit = (*DHC2)[i1];
          if(aHit->GetLayerID()==i2) aHit->Print();
        }
      }
    }

    if(ECHC) {
      int iHit = 0;
      double totalE = 0.;
      for(int i1=0;i1<80;i1++) {
        EmCalorimeterHit* aHit = (*ECHC)[i1];
        double eDep = aHit->GetEdep();
        if(eDep>0.) {
          iHit++;
          totalE += eDep;
        }
      }
      G4cout << "EM Calorimeter has " << iHit << " hits. Total Edep is " << totalE/CLHEP::MeV << " (MeV)" << G4endl;
    }

    if(HCHC) {
      int iHit = 0;
      double totalE = 0.;
      for(int i1=0;i1<20;i1++) {
        HadCalorimeterHit* aHit = (*HCHC)[i1];
        double eDep = aHit->GetEdep();
        if(eDep>0.) {
          iHit++;
          totalE += eDep;
        }
      }
      G4cout << "Hadron Calorimeter has " << iHit << " hits. Total Edep is " << totalE/CLHEP::MeV << " (MeV)" << G4endl;
    }
  }

public:
  EventAction()
  :m_messenger(get_me())
  ,verboseLevel(1)
  ,m_cloud_auto_cnv_limit(-1)
  ,m_build_plots(false)
  ,m_dc1Hits(0)
  ,m_dc2Hits(0)
  ,m_dc1XY(0)
  ,m_dc2XY(0)
  ,m_evstof(0)
  {
    create_histos();
  }

  virtual ~EventAction() {
    delete m_dc1Hits;
    delete m_dc2Hits;
    delete m_dc1XY;
    delete m_dc2XY;
    delete m_evstof;
  }
protected:
  EventAction(const EventAction&):m_messenger(get_me()){}
  EventAction& operator=(const EventAction&){return *this;}

public:
  void create_histos(){
    delete m_dc1Hits;
    delete m_dc2Hits;
    delete m_dc1XY;
    delete m_dc2XY;
    delete m_evstof;

    m_dc1Hits = new inlib::histo::h1d("Drift Chamber 1 # Hits",50,0,50);
    m_dc2Hits = new inlib::histo::h1d("Drift Chamber 2 # Hits",50,0,50);
    m_dc1XY = new inlib::histo::c2d("Drift Chamber 1 X vs Y",m_cloud_auto_cnv_limit);
    m_dc2XY = new inlib::histo::c2d("Drift Chamber 2 X vs Y",m_cloud_auto_cnv_limit);
    m_evstof = new inlib::histo::c2d("EDep vs Time-of-flight",m_cloud_auto_cnv_limit);
  }

//void reset_histos(){
//  m_dc1Hits->reset();
//  m_dc2Hits->reset();
//  m_dc1XY->reset();
//  m_dc2XY->reset();
//  m_evstof->reset();
//}

public:
  void SetVerbose(G4int val) { verboseLevel = val; }
  G4int GetVerbose() const { return verboseLevel; }

  int clouds_auto_cnv_limit() const {return m_cloud_auto_cnv_limit;}
  void set_clouds_auto_cnv_limit(int a_value) {
    if(a_value==m_cloud_auto_cnv_limit) return;
    m_cloud_auto_cnv_limit = a_value;
    //NOTE : avoid to recreate clouds ?
    delete m_dc1XY;
    delete m_dc2XY;
    delete m_evstof;
    m_dc1XY = new inlib::histo::c2d("Drift Chamber 1 X vs Y",m_cloud_auto_cnv_limit);
    m_dc2XY = new inlib::histo::c2d("Drift Chamber 2 X vs Y",m_cloud_auto_cnv_limit);
    m_evstof = new inlib::histo::c2d("EDep vs Time-of-flight",m_cloud_auto_cnv_limit);
  }
  bool build_plots() const {return m_build_plots;}
protected:
  class EventActionMessenger: public G4UImessenger {
    typedef G4UImessenger parent;
  public:
    virtual void SetNewValue(G4UIcommand * command,G4String newValue) {
      if(command==verboseCmd) m_target.SetVerbose(verboseCmd->GetNewIntValue(newValue));
    }
    virtual G4String GetCurrentValue(G4UIcommand * command) {
      G4String cv;
      if(command==verboseCmd)  cv = verboseCmd->ConvertToString(m_target.GetVerbose());
      return cv;
    }
  public:
    EventActionMessenger(EventAction& mpga):m_target(mpga) {
      verboseCmd = new G4UIcmdWithAnInteger("/mydet/verbose",this);
      verboseCmd->SetGuidance("Verbose level for each event.");
      verboseCmd->SetGuidance(" Event summary will be displayed for every 'level' events.");
      verboseCmd->SetParameterName("level",true);
      verboseCmd->SetRange("level>=0");
      verboseCmd->SetDefaultValue(1);
    }
    virtual ~EventActionMessenger() {delete verboseCmd;}
  private:
    EventActionMessenger(const EventActionMessenger& a_from):parent(a_from),m_target(a_from.m_target) {}
    EventActionMessenger& operator=(const EventActionMessenger&) {return *this;}
  private:
    EventAction& m_target;
  private: //commands
    G4UIcmdWithAnInteger*  verboseCmd;
  };

  EventAction& get_me() {return *this;}
private:
  EventActionMessenger m_messenger;
  G4int verboseLevel;
  int m_cloud_auto_cnv_limit;
  bool m_build_plots;
public:
  inlib::histo::h1d* m_dc1Hits;
  inlib::histo::h1d* m_dc2Hits;
  inlib::histo::c2d* m_dc1XY;
  inlib::histo::c2d* m_dc2XY;
  inlib::histo::c2d* m_evstof;
};

}

#endif
