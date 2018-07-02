# link order (from src/sys/binmake.gmk) :
#  LDLIBS2 += -lG4analysis
#             -lG4error_propagation
#             -lG4readout
#             -lG4physicslists
#             -lG4run
#             -lG4event
#             -lG4tracking
#             -lG4parmodels
#             -lG4processes
#             -lG4digits_hits
#             -lG4track
#             -lG4particles
#             -lG4geometry
#             -lG4materials
#             -lG4graphics_reps
#             -lG4intercoms
#             -lG4global
#             -lG4clhep

# G4readout G4physicslists G4run G4event G4tracking G4processes G4digits_hits
# G4track G4particles G4geometry G4graphics_reps G4materials
# G4intercoms G4global CLHEP

# list of dirs produced with ../mgr/g42mk (that produces a g4.mk file)
# but reorder according the upper :
#G4HOME := $(LOCAL_PATH)/../../../inexlib/ourex/geant4
G4HOME := $(LOCAL_PATH)/../../../inexlib/ourex/geant4.10.03.p01

GEANT4_1_SRC_FILES := \
 $(subst jni,.,$(wildcard $(G4HOME)/source/externals/clhep/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/global/HEPNumerics/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/global/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/intercoms/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/graphics_reps/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/materials/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/biasing/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/divisions/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/magneticfield/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/navigation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/solids/BREPS/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/solids/Boolean/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/solids/CSG/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/solids/specific/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/geometry/volumes/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/adjoint/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/bosons/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/hadrons/barions/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/hadrons/ions/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/hadrons/mesons/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/leptons/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/shortlived/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/particles/utils/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/track/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/digits_hits/detector/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/digits_hits/digits/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/digits_hits/hits/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/digits_hits/scorer/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/digits_hits/utils/src/*.cc))

GEANT4_2_SRC_FILES := \
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/biasing/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/cuts/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/decay/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/adjoint/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/dna/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/dna/models/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/dna/molecules/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/dna/molecules/types/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/dna/processes/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/dna/utils/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/highenergy/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/lowenergy/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/muons/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/pii/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/polarisation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/standard/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/utils/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/electromagnetic/xrays/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/cross_sections/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/abrasion/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/binary_cascade/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/cascade/cascade/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/cascade/evaporation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/cascade/utils/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/chiral_inv_phase_space/body/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/chiral_inv_phase_space/cross_sections/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/chiral_inv_phase_space/fragmentation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/chiral_inv_phase_space/interface/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/chiral_inv_phase_space/processes/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/coherent_elastic/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/ablation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/evaporation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/fermi_breakup/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/fission/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/gem_evaporation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/handler/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/multifragmentation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/photon_evaporation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/de_excitation/util/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/em_dissociation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/high_energy/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/fission/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/im_r_matrix/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/incl/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/inclxx/incl_physics/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/inclxx/interface/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/inclxx/utils/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/isotope_production/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/lend/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/lepto_nuclear/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/lll_fission/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/low_energy/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/neutron_hp/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/particle_hp/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/parton_string/diffraction/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/parton_string/hadronization/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/parton_string/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/parton_string/qgsm/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/photolepton_hadron/muon_nuclear/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/pre_equilibrium/exciton_model/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/qmd/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/quasi_elastic/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/radioactive_decay/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/rpg/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/theo_high_energy/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/models/util/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/processes/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/stopping/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/hadronic/util/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/management/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/optical/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/parameterisation/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/scoring/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/processes/transportation/src/*.cc))

GEANT4_3_SRC_FILES := \
 $(subst jni,.,$(wildcard $(G4HOME)/source/parameterisations/gflash/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/tracking/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/event/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/run/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/physics_lists/lists/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/physics_lists/builders/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/readout/src/*.cc))\
 $(subst jni,.,$(wildcard $(G4HOME)/source/error_propagation/src/*.cc))

# $(subst jni,.,$(wildcard $(G4HOME)/source/persistency/ascii/src/*.cc))\
# $(subst jni,.,$(wildcard $(G4HOME)/source/persistency/mctruth/src/*.cc))\
# $(subst jni,.,$(wildcard $(G4HOME)/source/analysis/src/*.cc))
#
