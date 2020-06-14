.PHONY: clean All

debug: 
	@echo "----------Building project:[ linux_rtt - Simulator (Debug) ]----------"
	@"$(MAKE)" -f  "linux_rtt_simulator.mk" PreBuild && "$(MAKE)" -f  "linux_rtt_simulator.mk" && "$(MAKE)" -f  "linux_rtt_simulator.mk" PostBuild

debug-run: 
	@echo "----------Building project:[ linux_rtt - Simulator (Debug) ]----------"
	@"$(MAKE)" -f  "linux_rtt_simulator.mk" PreBuild && "$(MAKE)" -f  "linux_rtt_simulator.mk" && "$(MAKE)" -f  "linux_rtt_simulator.mk" PostBuild
	@"./Solar2DSimulator/Solar2DSimulator_debug"

release: 
	@echo "----------Building project:[ linux_rtt - Simulator (Release) ]----------"
	@"$(MAKE)" -f  "linux_rtt_simulator_release.mk" PreBuild && "$(MAKE)" -f  "linux_rtt_simulator_release.mk" && "$(MAKE)" -f  "linux_rtt_simulator_release.mk" PostBuild

release-run:
	@echo "----------Building project:[ linux_rtt - Simulator (Release) ]----------"
	@"$(MAKE)" -f  "linux_rtt_simulator_release.mk" PreBuild && "$(MAKE)" -f  "linux_rtt_simulator_release.mk" && "$(MAKE)" -f  "linux_rtt_simulator_release.mk" PostBuild
	@"./Solar2DSimulator/Solar2DSimulator_release"

distribution:
	@"$(MAKE)" -f  "linux_rtt_simulator_release.mk" clean
	@echo "----------Building project:[ linux_rtt - Simulator (Release) ]----------"
	@"$(MAKE)" -f  "linux_rtt_simulator_release.mk" PreBuild && "$(MAKE)" -f  "linux_rtt_simulator_release.mk" && "$(MAKE)" -f  "linux_rtt_simulator_release.mk"
	@echo "----------Building project:[ linux_rtt - Simulator (Template) ]----------"
	@"$(MAKE)" -f  "linux_rtt_simulator_template.mk" clean
	@"$(MAKE)" -f  "linux_rtt_simulator_template.mk" PreBuild && "$(MAKE)" -f  "linux_rtt_simulator_template.mk" && "$(MAKE)" -f  "linux_rtt_simulator_template.mk" PostBuild
	tar -czf ./Solar2DSimulator/linuxTemplate.tgz ./Solar2DSimulator/linuxTemplate

pre-build:
	make -f lua2cpp.mk

clean:
	rm -f ./Solar2DSimulator/Solar2DSimulator_debug
	rm -f ./Solar2DSimulator/Solar2DSimulator_release
	rm -f ./Solar2DSimulator/Solar2DSimulator_template
	@echo "----------Cleaning project:[ linux_rtt - Simulator ]----------"
	@"$(MAKE)" -f  "linux_rtt_simulator.mk" clean
	@"$(MAKE)" -f  "linux_rtt_simulator_release.mk" clean
	@"$(MAKE)" -f  "linux_rtt_simulator_template.mk" clean
