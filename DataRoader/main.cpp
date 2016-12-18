
#include"Data.h"
#include"main.h"


int	main(void)
{
	if(RoadSubTable("SubTable.txt")	== -1)
		return -1;

	if(RoadSubjects("Subjects.txt") == -1)
		return -1;

	if(RoadTeacherGroup("TeacherGroup.txt") == -1)
		return -1;

	if(RoadRoomGroup("RoomGroup.txt") == -1)
		return -1;

	if(RoadClassGroup("ClassGroup.txt") == -1)
		return -1;

	if(RoadEvaluationTable("AtbGroup.txt") == -1)
		return -1;

	if(RoadEvaluationAtb("Attributes.txt") == -1)
		return -1;

	return 0;
}