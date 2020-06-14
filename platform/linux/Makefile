.PHONY: clean All

debug: 
	@echo "----------Building project:[ Simulator (Debug) ]----------"
	@"$(MAKE)" -j4 -f "linux_rtt_simulator_debug.mk"

debug-run: 
	@echo "----------Building project:[ Simulator (Debug) ]----------"
	@"$(MAKE)" -j4 -f "linux_rtt_simulator_debug.mk"
	@"./Solar2DSimulator/Solar2DSimulator_debug"

release: 
	@echo "----------Building project:[ Simulator (Release) ]----------"
	@"$(MAKE)" -j4 -f "linux_rtt_simulator_release.mk"

release-run:
	@echo "----------Building project:[ Simulator (Release) ]----------"
	@"$(MAKE)" -j4 -f "linux_rtt_simulator_release.mk"
	@"./Solar2DSimulator/Solar2DSimulator_release"

distribution:
	@echo "----------Building project:[ Simulator, Templates (Distribution) ]----------"
	@"$(MAKE)" -f "linux_rtt_simulator_debug.mk" clean
	@"$(MAKE)" -f "linux_rtt_simulator_release.mk" clean
	@"$(MAKE)" -j4 -f "linux_rtt_simulator_release.mk"
	@"$(MAKE)" -j4 -f "linux_rtt_template_x64.mk"
	##@"$(MAKE)" -j4 -f "linux_rtt_template_x86.mk"
	##@"$(MAKE)" -j4 -f "linux_rtt_template_arm.mk"
	mv Solar2DSimulator/Solar2DSimulator_release Solar2DSimulator/Solar2DSimulator 

clean:
	@echo "----------Cleaning project:[ linux_rtt - Simulator ]----------"
	@"$(MAKE)" -f "linux_rtt_simulator_debug.mk" clean
	@"$(MAKE)" -f "linux_rtt_simulator_release.mk" clean
