extern const double pi = 3.141592653589;

bool pusherType = 0; //0 - progressive, 1 - rotating

double maxShift = 100;
double stressDegree = 35;
double pusherLength = 150;

double aw = 0;

double eccentricity = 220;
bool isEccChecked = false;
double s_0 = 220;
double minRadius = 220;
double trundle_r = 220;
double trundle_k = 0.25;

double f_phDegree = 50;
double c_phDegree = 20;


double fs_degree = 20;
double cs_degree = 360 - (f_phDegree + fs_degree + c_phDegree);

int far_phase_law = 0;
int close_phase_law = 0;

int rotationDirection = 0; // 0 - clockwise, 1 - counterclockwise
