#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Base class
class Student {
	protected:
    	std::string first_name;
    	std::string last_name;
    	double gpa;
    	int graduation_year;
    	std::string graduation_semester;
    	int enrolled_year;
    	std::string enrolled_semester;
    	std::string graduation_status; 

	public:
    	// constructor
	Student() : first_name(""), last_name(""), gpa(0.0), graduation_year(0), graduation_semester(""), enrolled_year(0), enrolled_semester(""), graduation_status("") {}

    	// destructor
    	~Student() {}

    	// getters
	std::string getFirstName() {
		return first_name; }
    	std::string getLastName() {
		return last_name; }
    	double getGPA() {
		return gpa; }
    	int getGraduationYear() {
		return graduation_year; }
    	std::string getGraduationSemester() {
		return graduation_semester; }
    	int getEnrolledYear() {
		return enrolled_year; }
    	std::string getEnrolledSemester() {
		return enrolled_semester; }
    	std::string getDegreeType() {
		return graduation_status; }

    	// setters
    	void setName(const std::string& first, const std::string& last) {
        	first_name = first;
        	last_name = last;
    	}
    	void setGPA(double newGPA) {
		gpa = newGPA; }
    	void setGraduationYear(int year) {
		graduation_year = year; }
    	void setGraduationSemester(const std::string& semester) { 
		graduation_semester = semester; }
    	void setEnrolledYear(int year) {
		enrolled_year = year; }
    	void setEnrolledSemester(const std::string& semester) {
		enrolled_semester = semester; }
    	void setGraduationStatus(const std::string& status) {
		graduation_status = status; }

    	void printInfo(std::ofstream& outfile)const {
        	outfile << "Name: " << first_name << " " << last_name << std::endl;
        	outfile << "GPA: " << gpa << std::endl;
        	outfile << "Graduation: " << graduation_semester << " " << graduation_year << std::endl;
        	outfile << "Enrolled: " << enrolled_semester << " " << enrolled_year << std::endl;
        	outfile << "Graduation Status: " << graduation_status << std::endl;
    	}
	};

// derived class
class Art_Student : public Student {
	private:
    	std::string art_emphasis;

	public:
    	// constructor
    	Art_Student() : Student(), art_emphasis("") {}

    	// destructor
    	~Art_Student() {}

    	// getter
    	std::string getArtEmphasis() const {
		return art_emphasis; }

    	// setter
    	void setArtEmphasis(const std::string& emphasis) {
		art_emphasis = emphasis; }

    	void printInfo(std::ofstream& outfile)  {
        	Student::printInfo(outfile);
        	outfile << "Art Emphasis: " << art_emphasis << std::endl;
        	outfile << "--------------------" << std::endl;
    		}
	};

// derived class
class Physics_Student : public Student {
	private:
    	std::string physics_emphasis;

	public:
    	// constructor
    	Physics_Student() : Student(), physics_emphasis("") {}

    	// destructor
    	~Physics_Student() {}

    	// getter
    	std::string getPhysicsEmphasis() const {
		return physics_emphasis; }

    	// setter
    	void setPhysicsEmphasis(const std::string& Emphasis) {
		physics_emphasis = Emphasis; }
	//override 
    	void printInfo(std::ofstream& outfile) {
        	Student::printInfo(outfile);
        	outfile << "Physics Emphasis: " << physics_emphasis << std::endl;
        	outfile << "--------------------" << std::endl;
    		}
	};

int main() {
	std::vector<Art_Student*> art_students;
	std::vector<Physics_Student*> physics_students;

	// 5 art students
	std::string artFirstNames[] = {"Ann", "Cynth", "Rose", "Em", "Jenn"};
	std::string artLastNames[] = {"Sandal", "Ayala", "Smith", "Bryant", "lee"};
	for (int i = 0; i < 5; i++) {
		art_students.push_back(new Art_Student());
		art_students[i]->setName(artFirstNames[i], artLastNames[i]);
		art_students[i]->setGPA(3.0 + (i * 0.3));
		art_students[i]->setGraduationYear(2025 + i);
		art_students[i]->setGraduationSemester(i % 2 == 0 ? "Fall" : "Spring");
		art_students[i]->setEnrolledYear(2021 + i);
		art_students[i]->setEnrolledSemester(i % 2 == 0 ? "Spring" : "Fall");
		art_students[i]->setGraduationStatus("Undergrad");
		if (i == 0)
			art_students[i]->setArtEmphasis("Art Studio");
		else if (i == 1)
			art_students[i]->setArtEmphasis("Art History");
		else art_students[i]->setArtEmphasis("Art Education");
	}

	// 5 physics students
	std::string physicsFirstNames[] = {"Jan", "Jamm", "Mechel", "Fel", "Zach"};
	std::string physicsLastNames[] = {"Bolt", "Mayer", "Castro", "Balzrete", "Jones"};
	for (int i = 0; i < 5; i++) {
		physics_students.push_back(new Physics_Student());
		physics_students[i]->setName(physicsFirstNames[i], physicsLastNames[i]);
		physics_students[i]->setGPA(3.3 + (i * 0.2));
		physics_students[i]->setGraduationYear(2026 + i);
		physics_students[i]->setGraduationSemester(i % 2 == 0 ? "Spring" : "Fall");
		physics_students[i]->setEnrolledYear(2022 + i);
		physics_students[i]->setEnrolledSemester(i % 2 == 0 ? "Fall" : "Spring");
		physics_students[i]->setGraduationStatus("Grad");
		if (i % 2 == 0)
			physics_students[i]->setPhysicsEmphasis("Biophysics");
		else physics_students[i]->setPhysicsEmphasis("Earth and Planetary Sciences");
	}

	// student info to student_info.dat file
	std::ofstream outfile("student_info.dat");
	
	outfile << "=== Art Students ===" << std::endl;
	for (Art_Student* student : art_students) {
	student->printInfo(outfile);
	}

	outfile << "\n=== Physics Students===" << std::endl;
	for (Physics_Student* student : physics_students) {
        student->printInfo(outfile);
	}

	outfile.close();

	// delete allocated memory
	for (Art_Student* student : art_students) {
        delete student;
	}
	for (Physics_Student* student : physics_students) {
        delete student;
	}

	std::cout << "Student information is in the student_info.dat file." << std::endl;
	return 0;
}
