make:
	g++ -Wall -Wextra code/header/common/class/Controller.h code/header/common/class/DAO.h code/header/common/class/MenuController.h code/header/common/class/MenuItemSet.h code/header/common/interface/IModel.h code/header/common/interface/IService.h code/header/common/enums.h code/header/common/FindResult.h code/src/class/common/Controller.cpp code/src/class/common/DAO.cpp code/src/class/common/MenuController.cpp code/src/class/common/MenuItemSet.cpp code/header/module/login/LoginController.h code/src/class/module/login/LoginController.cpp code/header/module/meeting-point/MeetingPointController.h code/header/module/meeting-point/MeetingPointDAO.h code/header/module/meeting-point/MeetingPointModel.h code/header/module/meeting-point/MeetingPointService.h code/src/class/module/meeting-point/MeetingPointController.cpp code/src/class/module/meeting-point/MeetingPointDAO.cpp code/src/class/module/meeting-point/MeetingPointModel.cpp code/src/class/module/meeting-point/MeetingPointService.cpp code/header/module/reject-type/RejectTypeController.h code/header/module/reject-type/RejectTypeDAO.h code/header/module/reject-type/RejectTypeModel.h code/header/module/reject-type/RejectTypeService.h code/src/class/module/reject-type/RejectTypeController.cpp code/src/class/module/reject-type/RejectTypeDAO.cpp code/src/class/module/reject-type/RejectTypeModel.cpp code/src/class/module/reject-type/RejectTypeService.cpp code/header/module/scheduling/SchedulingController.h code/header/module/scheduling/SchedulingDAO.h code/header/module/scheduling/SchedulingModel.h code/header/module/scheduling/SchedulingService.h code/src/class/module/scheduling/SchedulingController.cpp code/src/class/module/scheduling/SchedulingDAO.cpp code/src/class/module/scheduling/SchedulingModel.cpp code/src/class/module/scheduling/SchedulingService.cpp code/header/module/user/UserController.h code/header/module/user/UserDAO.h code/header/module/user/UserModel.h code/header/module/user/UserService.h code/src/class/module/user/UserController.cpp code/src/class/module/user/UserDAO.cpp code/src/class/module/user/UserModel.cpp code/src/class/module/user/UserService.cpp code/src/main.cpp -o trash-recycling

main: common-cpp
	g++ -Wall -Wextra code/src/main.cpp

run:
	./trash-recycling

common-h:
	g++ -Wall -Wextra code/header/common/class/Controller.h code/header/common/class/DAO.h code/header/common/class/MenuController.h code/header/common/class/MenuItemSet.h code/header/common/interface/IModel.h code/header/common/interface/IService.h code/header/common/enums.h code/header/common/FindResult.h

common-cpp: common-h reject-type
	g++ -Wall -Wextra code/src/class/common/Controller.cpp code/src/class/common/DAO.cpp code/src/class/common/MenuController.cpp code/src/class/common/MenuItemSet.cpp code/src/main.cpp

login: meeting-point user
	g++ -Wall -Wextra code/header/module/login/LoginController.h code/src/class/module/login/LoginController.cpp

meeting-point: common-cpp
	g++ -Wall -Wextra code/header/module/meeting-point/MeetingPointController.h code/header/module/meeting-point/MeetingPointDAO.h code/header/module/meeting-point/MeetingPointModel.h code/header/module/meeting-point/MeetingPointService.h code/src/class/module/meeting-point/MeetingPointController.cpp code/src/class/module/meeting-point/MeetingPointDAO.cpp code/src/class/module/meeting-point/MeetingPointModel.cpp code/src/class/module/meeting-point/MeetingPointService.cpp

reject-type: common-cpp main
	g++ -Wall -Wextra code/header/module/reject-type/RejectTypeController.h code/header/module/reject-type/RejectTypeDAO.h code/header/module/reject-type/RejectTypeModel.h code/header/module/reject-type/RejectTypeService.h code/src/class/module/reject-type/RejectTypeController.cpp code/src/class/module/reject-type/RejectTypeDAO.cpp code/src/class/module/reject-type/RejectTypeModel.cpp code/src/class/module/reject-type/RejectTypeService.cpp

scheduling:
	g++ -Wall -Wextra code/header/module/scheduling/SchedulingController.h code/header/module/scheduling/SchedulingDAO.h code/header/module/scheduling/SchedulingModel.h code/header/module/scheduling/SchedulingService.h code/src/class/module/scheduling/SchedulingController.cpp code/src/class/module/scheduling/SchedulingDAO.cpp code/src/class/module/scheduling/SchedulingModel.cpp code/src/class/module/scheduling/SchedulingService.cpp

user:
	g++ -Wall -Wextra code/header/module/user/UserController.h code/header/module/user/UserDAO.h code/header/module/user/UserModel.h code/header/module/user/UserService.h code/src/class/module/user/UserController.cpp code/src/class/module/user/UserDAO.cpp code/src/class/module/user/UserModel.cpp code/src/class/module/user/UserService.cpp
