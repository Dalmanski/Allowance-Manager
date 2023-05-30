#pragma once

#include <fstream>
#include <msclr/marshal_cppstd.h> // Include this header for string conversion
#include <string>
#include <sstream>

namespace AllowanceManager {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for Intro
	/// </summary>
	public ref class Intro : public System::Windows::Forms::Form
	{
	public:
		Intro(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Intro()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DateTimePicker^ dateTimePicker1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::Label^ labelWeekRange;
	private: System::Windows::Forms::Label^ labelTotalPrice;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::ComboBox^ comboBoxDay;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::CheckBox^ checkBox1;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void SaveDataToFile()
		{
			String^ fileName = "data.csv";
			// Open the file in append mode
			std::ofstream file(msclr::interop::marshal_as<std::string>(fileName), std::ofstream::app);
			// Check if the file was successfully opened
			if (file.is_open()) {
				// Iterate through each row in the DataGridView
				//for (int rowIndex = 0; rowIndex < dataGridView1->RowCount; rowIndex++) {
					int rowIndex = dataGridView1->RowCount-1;
					// Get the date, product, and price from the respective cells
					String^ date = "";
					if (dataGridView1->Rows[rowIndex]->Cells[0]->Value != nullptr) {
						date = dataGridView1->Rows[rowIndex]->Cells[0]->Value->ToString();
					}
					String^ product = "";
					if (dataGridView1->Rows[rowIndex]->Cells[1]->Value != nullptr) {
						product = dataGridView1->Rows[rowIndex]->Cells[1]->Value->ToString();
					}
					String^ price = "";
					if (dataGridView1->Rows[rowIndex]->Cells[2]->Value != nullptr) {
						price = dataGridView1->Rows[rowIndex]->Cells[2]->Value->ToString();
					}
					// Write the data to the file
					file << msclr::interop::marshal_as<std::string>(date) << "|"
						<< msclr::interop::marshal_as<std::string>(product) << "|"
						<< msclr::interop::marshal_as<std::string>(price) << "\n";
				//}
				// Close the file
				file.close();
			}
			else {
				// Failed to open the file, show an error message
				MessageBox::Show("Failed to save data.", "Save Data", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
//-----------------------------------------------------------------------------------------------------------------------
	private: void LoadDataForSelectedDate() {
		// Get the selected date from the DateTimePicker
		DateTime selectedDate = dateTimePicker1->Value;
		// Convert the selected date to the desired format ("MMMM dd,yyyy")
		String^ selectedDateString = selectedDate.ToString("MMMM dd,yyyy");
		// Load data from file and populate the DataGridView for the selected date
		LoadDataFromFile(selectedDateString);
	}
//-----------------------------------------------------------------------------------------------------------------------
	// Function to load data from file and populate DataGridView based on the selected date
	void LoadDataFromFile(String^ selectedDate) {
		std::string fileName = "data.csv";
		// Check if the file exists before attempting to load data
		std::ifstream file(fileName);
		if (!file) {
			// File does not exist, return or display an error message
			return;
		}
		// Clear existing DataGridView data and columns
		dataGridView1->Rows->Clear();
		dataGridView1->Columns->Clear();
		// Add columns to the DataGridView
		dataGridView1->Columns->Add("Column1", "Date:");
		dataGridView1->Columns->Add("Column2", "Product:");
		dataGridView1->Columns->Add("Column3", "Price:");
		std::string line;
		while (std::getline(file, line)) {
			String^ row = gcnew String(line.c_str());
			array<String^>^ cells = row->Split('|');
			// Skip the row if it doesn't contain enough cells
			if (cells->Length < 3) {
				continue;
			}
			// Check if the date in the first column matches the selected date
			if (cells[0] == selectedDate) {
				// Populate the cells in the new row
				int rowIndex = dataGridView1->Rows->Add();
				dataGridView1->Rows[rowIndex]->Cells[0]->Value = cells[0]; // Date column
				dataGridView1->Rows[rowIndex]->Cells[1]->Value = cells[1]; // Product column
				dataGridView1->Rows[rowIndex]->Cells[2]->Value = cells[2]; // Price column
			}
		}
		file.close();
	}
//-----------------------------------------------------------------------------------------------------------------------
	double TotalPriceOfWeek() {
		DateTime selectedDate = dateTimePicker1->Value;
		/*int lastDateNum;
		if (comboBoxDay->Text == "Monday") {
			lastDateNum = 5;
		}
		else if (comboBoxDay->Text == "Tuesday") {
			lastDateNum = 4;
		}
		else if (comboBoxDay->Text == "Wednesday") {
			lastDateNum = 3;
		}
		else if (comboBoxDay->Text == "Thursday") {
			lastDateNum = 2;
		}
		else if (comboBoxDay->Text == "Friday") {
			lastDateNum = 1;
		}
		else if (comboBoxDay->Text == "Saturday") {
			lastDateNum = 0;
		}
		else if (comboBoxDay->Text == "Sunday") {
			lastDateNum = 6;
		}*/
		DateTime startDate;
		DateTime endDate;
		if (selectedDate.DayOfWeek == DayOfWeek::Sunday) {
			startDate = selectedDate.AddDays(-6);
			endDate = selectedDate;
		}
		else {
			startDate = selectedDate.AddDays(-(int)selectedDate.DayOfWeek + 1);
			endDate = startDate.AddDays(6);
		}
		// Display the week range in the desired format
		String^ weekRange = String::Format("Your week is from {0:MMMM dd,yyyy} to {1:MMMM dd,yyyy}", startDate, endDate);
		labelWeekRange->Text = weekRange;
		// Read data from the file and calculate the sum of prices within the week
		std::string fileName = "data.csv";
		std::ifstream file(fileName);
		if (!file) {
			// File does not exist, return or display an error message
			return 0.0;
		}
		double totalPrice = 0.0;
		std::string line;
		while (std::getline(file, line)) {
			String^ row = gcnew String(line.c_str());
			array<String^>^ cells = row->Split('|');
			// Skip the row if it doesn't contain enough cells
			if (cells->Length < 3) {
				continue;
			}
			// Parse the date from the first cell
			DateTime date;
			if (DateTime::TryParse(cells[0], date)) {
				date = date.AddDays(1);
				if (date >= startDate && date <= endDate) {
					double price;
					if (Double::TryParse(cells[2], price)) {
						totalPrice += price;
					}
				}
			}

		}
		file.close();
		// Display the total price in a label
		labelTotalPrice->Text = "Total Price in this Week: P" + totalPrice.ToString("N2");
		// Return the calculated total price
		return totalPrice;
	}
//-----------------------------------------------------------------------------------------------------------------------
		// Function to load all data from file and populate DataGridView
		void LoadDataFromFileReadAll() {
		std::string fileName = "data.csv";
		// Check if the file exists before attempting to load data
		std::ifstream file(fileName);
		if (!file) {
			// File does not exist, return or display an error message
			return;
		}
		// Clear existing DataGridView data and columns
		dataGridView1->Rows->Clear();
		dataGridView1->Columns->Clear();
		// Add columns to the DataGridView
		dataGridView1->Columns->Add("Column1", "Date:");
		dataGridView1->Columns->Add("Column2", "Product:");
		dataGridView1->Columns->Add("Column3", "Price:");
		std::string line;
		while (std::getline(file, line)) {
			String^ row = gcnew String(line.c_str());
			array<String^>^ cells = row->Split('|');
			// Skip the row if it doesn't contain enough cells
			if (cells->Length < 3) {
				continue;
			}
			// Add a new row to the DataGridView
			int rowIndex = dataGridView1->Rows->Add();
			// Populate the cells in the new row
			dataGridView1->Rows[rowIndex]->Cells[0]->Value = cells[0]; // Date column
			dataGridView1->Rows[rowIndex]->Cells[1]->Value = cells[1]; // Product column
			dataGridView1->Rows[rowIndex]->Cells[2]->Value = cells[2]; // Price column
		}
		file.close();
	}
//-----------------------------------------------------------------------------------------------------------------------
		void SaveAllDataToFile() {
			std::string fileName = "data.csv";
			std::ofstream file(fileName);
			// Iterate through each row in the DataGridView
			for (int rowIndex = 0; rowIndex < dataGridView1->RowCount; rowIndex++) {
				// Iterate through each cell in the current row
				for (int columnIndex = 0; columnIndex < dataGridView1->ColumnCount; columnIndex++) {
					// Get the cell value and handle null values
					String^ cellValue = dataGridView1->Rows[rowIndex]->Cells[columnIndex]->Value != nullptr
						? dataGridView1->Rows[rowIndex]->Cells[columnIndex]->Value->ToString()
						: "";
					file << msclr::interop::marshal_as<std::string>(cellValue) << "|"; // Use a | to separate values
				}
				file << "\n"; // Add a new line after each row
			}
			file.close();
		}
//-----------------------------------------------------------------------------------------------------------------------
		void InitializeComponent(void)
		{
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->labelWeekRange = (gcnew System::Windows::Forms::Label());
			this->labelTotalPrice = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->comboBoxDay = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->BackgroundColor = System::Drawing::SystemColors::Control;
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Column1,
					this->Column2, this->Column3
			});
			this->dataGridView1->Enabled = false;
			this->dataGridView1->GridColor = System::Drawing::SystemColors::ControlLight;
			this->dataGridView1->Location = System::Drawing::Point(276, 32);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->ShowEditingIcon = false;
			this->dataGridView1->Size = System::Drawing::Size(444, 237);
			this->dataGridView1->TabIndex = 0;
			this->dataGridView1->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Intro::dataGridView1_CellValueChanged);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"Date:";
			this->Column1->Name = L"Column1";
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Product:";
			this->Column2->Name = L"Column2";
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Price:";
			this->Column3->Name = L"Column3";
			// 
			// textBox1
			// 
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Location = System::Drawing::Point(22, 147);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(200, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label1->Location = System::Drawing::Point(22, 129);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(103, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Product:            ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label2->Location = System::Drawing::Point(22, 190);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(104, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Price:                ";
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->Location = System::Drawing::Point(22, 81);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(200, 20);
			this->dateTimePicker1->TabIndex = 5;
			this->dateTimePicker1->ValueChanged += gcnew System::EventHandler(this, &Intro::dateTimePicker1_ValueChanged);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button1->Location = System::Drawing::Point(85, 256);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(71, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = L"ADD";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Intro::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button2->Location = System::Drawing::Point(58, 394);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(127, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"ERASE ALL DATA";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Intro::button2_Click);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->numericUpDown1->DecimalPlaces = 2;
			this->numericUpDown1->Location = System::Drawing::Point(22, 208);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(200, 20);
			this->numericUpDown1->TabIndex = 8;
			this->numericUpDown1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// labelWeekRange
			// 
			this->labelWeekRange->AutoSize = true;
			this->labelWeekRange->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->labelWeekRange->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->labelWeekRange->Location = System::Drawing::Point(276, 272);
			this->labelWeekRange->Name = L"labelWeekRange";
			this->labelWeekRange->Size = System::Drawing::Size(92, 15);
			this->labelWeekRange->TabIndex = 9;
			this->labelWeekRange->Text = L"labelWeekRange";
			// 
			// labelTotalPrice
			// 
			this->labelTotalPrice->AutoSize = true;
			this->labelTotalPrice->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->labelTotalPrice->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->labelTotalPrice->Location = System::Drawing::Point(546, 272);
			this->labelTotalPrice->Name = L"labelTotalPrice";
			this->labelTotalPrice->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->labelTotalPrice->Size = System::Drawing::Size(79, 15);
			this->labelTotalPrice->TabIndex = 10;
			this->labelTotalPrice->Text = L"labelTotalPrice";
			this->labelTotalPrice->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(-2, 1);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(247, 468);
			this->pictureBox1->TabIndex = 11;
			this->pictureBox1->TabStop = false;
			// 
			// comboBoxDay
			// 
			this->comboBoxDay->FormattingEnabled = true;
			this->comboBoxDay->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Monday", L"Tuesday", L"Wednesday", L"Thursday",
					L"Friday", L"Saturday", L"Sunday"
			});
			this->comboBoxDay->Location = System::Drawing::Point(445, 332);
			this->comboBoxDay->Name = L"comboBoxDay";
			this->comboBoxDay->Size = System::Drawing::Size(105, 21);
			this->comboBoxDay->TabIndex = 12;
			this->comboBoxDay->Text = L"Sunday";
			this->comboBoxDay->TextChanged += gcnew System::EventHandler(this, &Intro::comboBoxDay_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::LightGray;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label3->Location = System::Drawing::Point(411, 366);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(176, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"How much is your Allowance\?";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label4->Location = System::Drawing::Point(22, 63);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(98, 13);
			this->label4->TabIndex = 14;
			this->label4->Text = L"Select the date:";
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->numericUpDown2->DecimalPlaces = 2;
			this->numericUpDown2->Location = System::Drawing::Point(398, 382);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 9999, 0, 0, 0 });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(200, 20);
			this->numericUpDown2->TabIndex = 15;
			this->numericUpDown2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button3->Location = System::Drawing::Point(455, 412);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(82, 23);
			this->button3->TabIndex = 16;
			this->button3->Text = L"SEE RESULT";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Intro::button3_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Gainsboro;
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox2->Location = System::Drawing::Point(245, 299);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(513, 170);
			this->pictureBox2->TabIndex = 17;
			this->pictureBox2->TabStop = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::LightGray;
			this->label5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label5->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label5->Location = System::Drawing::Point(22, 16);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(147, 34);
			this->label5->TabIndex = 18;
			this->label5->Text = L"ALLOWANCE MANAGERs\r\nBY: DALMANSKI";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->label6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label6->Location = System::Drawing::Point(476, 11);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(38, 15);
			this->label6->TabIndex = 19;
			this->label6->Text = L"DEBT";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->label7->Location = System::Drawing::Point(89, 332);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(62, 13);
			this->label7->TabIndex = 20;
			this->label7->Text = L"OPTIONS";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::LightGray;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::SystemColors::ControlText;
			this->label8->Location = System::Drawing::Point(403, 315);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(195, 13);
			this->label8->TabIndex = 21;
			this->label8->Text = L"When do you get the Allowance\?";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(82, 362);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(74, 17);
			this->checkBox1->TabIndex = 22;
			this->checkBox1->Text = L"Edit Mode";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Intro::checkBox1_CheckedChanged);
			// 
			// Intro
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->ClientSize = System::Drawing::Size(750, 447);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->numericUpDown2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBoxDay);
			this->Controls->Add(this->labelTotalPrice);
			this->Controls->Add(this->labelWeekRange);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->dateTimePicker1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox2);
			this->Name = L"Intro";
			this->Text = L"Allowance Manager";
			this->Load += gcnew System::EventHandler(this, &Intro::Intro_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
//-----------------------------------------------------------------------------------------------------------------------
#pragma endregion
	private: bool editMode = false; // Variable to track edit mode state

	private: System::Void Intro_Load(System::Object^ sender, System::EventArgs^ e) {
		// Load the initial data based on the selected date
		LoadDataFromFile(dateTimePicker1->Value.ToString("MMMM dd,yyyy"));
		TotalPriceOfWeek();
	}
//-----------------------------------------------------------------------------------------------------------------------
	// Event handler for FormClosing event
	private: System::Void Intro_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		SaveDataToFile();
	}
//-----------------------------------------------------------------------------------------------------------------------
	// Event handler for CellValueChanged event
	private: System::Void dataGridView1_CellValueChanged(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		// Check if the value in the cell becomes empty
		if (e->RowIndex >= 0 && dataGridView1->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value == nullptr) {
			bool isRowEmpty = true;
			// Check if all cells in the row are empty
			for (int columnIndex = 0; columnIndex < dataGridView1->Columns->Count; columnIndex++) {
				if (dataGridView1->Rows[e->RowIndex]->Cells[columnIndex]->Value != nullptr) {
					isRowEmpty = false;
					break;
				}
			}
			// Remove the empty row
			if (isRowEmpty) {
				dataGridView1->Rows->RemoveAt(e->RowIndex);
			}
		}
		if (editMode) {
			// Save the changes to the file
			SaveAllDataToFile();
		}
	}
//-----------------------------------------------------------------------------------------------------------------------
	// Event handler for the "Add" button click event
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		System::DateTime selectedDate = dateTimePicker1->Value;
		System::DateTime currentDate = System::DateTime::Today;
		if (textBox1->Text != "" && static_cast<float>(numericUpDown1->Value) != 0 && selectedDate.Date == currentDate.Date) {
			// Retrieve product and price values from TextBoxes	
			String^ product = textBox1->Text;
			float Price = static_cast<float>(numericUpDown1->Value);
			// Format the price with two decimal places
			String^ price = Price.ToString("F2");
			// Display a message box to confirm the data deletion
			System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to add " + product + " with " + price + " pesos?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
			// Check the user's response
			if (result == System::Windows::Forms::DialogResult::Yes) {			
				// Convert the date to the desired format or extract the desired information
				System::String^ selectedDateText = selectedDate.ToString("MMMM dd,yyyy");
				// Create a new row with the date, product, and price values
				DataGridViewRow^ newRow = gcnew DataGridViewRow();
				newRow->CreateCells(dataGridView1);
				newRow->SetValues(selectedDateText, product, price);
				// Add the new row to the DataGridView
				dataGridView1->Rows->Add(newRow);
				// Clear the TextBoxes after adding the row
				textBox1->Clear();
				numericUpDown1->Value = 0;
				// After that, save automatically
				SaveDataToFile();
				TotalPriceOfWeek();
			}
		}
		else if (textBox1->Text != "" && static_cast<float>(numericUpDown1->Value) != 0 && selectedDate.Date != currentDate.Date) {
			// If the selected date is not equal to the current date
			System::Windows::Forms::MessageBox::Show("Make sure your Selected Date is equal to the Current Date.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
			else {
				// If the Textbox Product and Price are empty
				System::Windows::Forms::MessageBox::Show("Please fill up the Product and the Price.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
//-----------------------------------------------------------------------------------------------------------------------
	// To erase in a file
	// Event handler for the button click event
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		// Display a message box to confirm the data deletion
		System::Windows::Forms::DialogResult result = MessageBox::Show("Do you want to erase all the data?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
		// Check the user's response
		if (result == System::Windows::Forms::DialogResult::Yes) {
			// Open the "data.csv" file in write mode
			std::ofstream file("data.csv", std::ofstream::out | std::ofstream::trunc);
			// Check if the file was successfully opened
			if (file.is_open()) {
				// File opened successfully, close it
				file.close();
				// Clear existing DataGridView data and columns
				dataGridView1->Rows->Clear();
				dataGridView1->Columns->Clear();
				LoadDataFromFile(dateTimePicker1->Value.ToString("MMMM dd,yyyy"));
				// Show a message indicating that the data has been deleted
				MessageBox::Show("Data has been deleted.", "Delete Data", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				// Failed to open the file, show an error message
				MessageBox::Show("Failed to delete data.", "Delete Data", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
//-----------------------------------------------------------------------------------------------------------------------
	// Press the result button to get the allowance left.
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		// Get the selected day from the ComboBox
		String^ selectedDay = comboBoxDay->Text;
		if (selectedDay != "Select a Day to get Allowance") {
			// Get the current day of the week
			System::DayOfWeek currentDay = System::DateTime::Now.DayOfWeek;
			// Perform the if-else check
			if (selectedDay == currentDay.ToString()) {
				// Current day matches the selected day
				// Do something
				double YourAllowance = System::Convert::ToDouble(numericUpDown2->Value);
				double TotalPrice = TotalPriceOfWeek();
				double AllowanceNow = YourAllowance - TotalPrice;
				if (AllowanceNow > 0) {
					System::Windows::Forms::MessageBox::Show("Your allowance today is: P" + AllowanceNow.ToString("N2"), "Your Allowance Now", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else if (AllowanceNow == 0) {
					System::Windows::Forms::MessageBox::Show("You have P0.00 allowance.", "Better luck next time!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
				else if (AllowanceNow < 0) {
					System::Windows::Forms::MessageBox::Show("You have not enough allowance. The debt is: P" + AllowanceNow.ToString("N2"), "Ooooops...", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}
			else {
				// If not this day
				System::Windows::Forms::MessageBox::Show("This is not " + selectedDay + " today.", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
			}
		}
	}
//-----------------------------------------------------------------------------------------------------------------------
	private: System::Void comboBoxDay_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		TotalPriceOfWeek();
	}
//-----------------------------------------------------------------------------------------------------------------------
	// Event handler for the CheckBox's CheckedChanged event
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		editMode = checkBox1->Checked;

		// Enable or disable editing in the DataGridView
		dataGridView1->ReadOnly = !editMode;
		// Clear existing DataGridView data and columns
		dataGridView1->Rows->Clear();
		dataGridView1->Columns->Clear();
		// If editMode is true, load all data from file and populate the DataGridView
		if (editMode) {
			this->dataGridView1->Enabled = true;
			LoadDataFromFileReadAll();
		}
		else {
			this->dataGridView1->Enabled = false;
			LoadDataFromFile(dateTimePicker1->Value.ToString("MMMM dd,yyyy"));
		}
	}
//-----------------------------------------------------------------------------------------------------------------------
	// Event handler for the DataGridView's CellEndEdit event
	private: System::Void dataGridView1_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		// Check if edit mode is enabled
		if (editMode) {
			// Save the changes to the file
			SaveDataToFile();
		}
	}
//-----------------------------------------------------------------------------------------------------------------------
	private:System::Void dateTimePicker1_ValueChanged(System::Object ^ sender, System::EventArgs ^ e) {
		if (!editMode) {
			// Clear the DataGridView and load data for the selected date
			dataGridView1->Rows->Clear();
			dataGridView1->Columns->Clear();
			LoadDataFromFile(dateTimePicker1->Value.ToString("MMMM dd,yyyy"));
			TotalPriceOfWeek();
		}
	}
//-----------------------------------------------------------------------------------------------------------------------
};
}
