namespace Profesor
{
	partial class FormP
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormP));
			this.DGVProfesori = new System.Windows.Forms.DataGridView();
			this.Marca = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.Nume = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.Salariu = new System.Windows.Forms.DataGridViewTextBoxColumn();
			this.BTNCalculSalarii = new System.Windows.Forms.Button();
			this.BTNSaveDB = new System.Windows.Forms.Button();
			this.printDocument1 = new System.Drawing.Printing.PrintDocument();
			this.printPreviewDialog1 = new System.Windows.Forms.PrintPreviewDialog();
			this.BTNPrintare = new System.Windows.Forms.Button();
			this.BTNSaveXML = new System.Windows.Forms.Button();
			((System.ComponentModel.ISupportInitialize)(this.DGVProfesori)).BeginInit();
			this.SuspendLayout();
			// 
			// DGVProfesori
			// 
			this.DGVProfesori.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
			this.DGVProfesori.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Marca,
            this.Nume,
            this.Salariu});
			this.DGVProfesori.Location = new System.Drawing.Point(12, 12);
			this.DGVProfesori.Name = "DGVProfesori";
			this.DGVProfesori.Size = new System.Drawing.Size(343, 150);
			this.DGVProfesori.TabIndex = 0;
			// 
			// Marca
			// 
			this.Marca.HeaderText = "Marca";
			this.Marca.Name = "Marca";
			// 
			// Nume
			// 
			this.Nume.HeaderText = "Nume";
			this.Nume.Name = "Nume";
			// 
			// Salariu
			// 
			this.Salariu.HeaderText = "Salariu";
			this.Salariu.Name = "Salariu";
			// 
			// BTNCalculSalarii
			// 
			this.BTNCalculSalarii.Location = new System.Drawing.Point(12, 415);
			this.BTNCalculSalarii.Name = "BTNCalculSalarii";
			this.BTNCalculSalarii.Size = new System.Drawing.Size(75, 23);
			this.BTNCalculSalarii.TabIndex = 1;
			this.BTNCalculSalarii.Text = "Calcul Salarii";
			this.BTNCalculSalarii.UseVisualStyleBackColor = true;
			this.BTNCalculSalarii.Click += new System.EventHandler(this.BTNCalculSalarii_Click);
			// 
			// BTNSaveDB
			// 
			this.BTNSaveDB.Location = new System.Drawing.Point(93, 415);
			this.BTNSaveDB.Name = "BTNSaveDB";
			this.BTNSaveDB.Size = new System.Drawing.Size(75, 23);
			this.BTNSaveDB.TabIndex = 2;
			this.BTNSaveDB.Text = "Salvare DB";
			this.BTNSaveDB.UseVisualStyleBackColor = true;
			this.BTNSaveDB.Click += new System.EventHandler(this.BTNSaveDB_Click);
			// 
			// printDocument1
			// 
			this.printDocument1.PrintPage += new System.Drawing.Printing.PrintPageEventHandler(this.printDocument1_PrintPage);
			// 
			// printPreviewDialog1
			// 
			this.printPreviewDialog1.AutoScrollMargin = new System.Drawing.Size(0, 0);
			this.printPreviewDialog1.AutoScrollMinSize = new System.Drawing.Size(0, 0);
			this.printPreviewDialog1.ClientSize = new System.Drawing.Size(400, 300);
			this.printPreviewDialog1.Document = this.printDocument1;
			this.printPreviewDialog1.Enabled = true;
			this.printPreviewDialog1.Icon = ((System.Drawing.Icon)(resources.GetObject("printPreviewDialog1.Icon")));
			this.printPreviewDialog1.Name = "printPreviewDialog1";
			this.printPreviewDialog1.Visible = false;
			// 
			// BTNPrintare
			// 
			this.BTNPrintare.Location = new System.Drawing.Point(174, 415);
			this.BTNPrintare.Name = "BTNPrintare";
			this.BTNPrintare.Size = new System.Drawing.Size(75, 23);
			this.BTNPrintare.TabIndex = 3;
			this.BTNPrintare.Text = "Print";
			this.BTNPrintare.UseVisualStyleBackColor = true;
			this.BTNPrintare.Click += new System.EventHandler(this.button1_Click);
			// 
			// BTNSaveXML
			// 
			this.BTNSaveXML.Location = new System.Drawing.Point(255, 415);
			this.BTNSaveXML.Name = "BTNSaveXML";
			this.BTNSaveXML.Size = new System.Drawing.Size(75, 23);
			this.BTNSaveXML.TabIndex = 4;
			this.BTNSaveXML.Text = "Save XML";
			this.BTNSaveXML.UseVisualStyleBackColor = true;
			this.BTNSaveXML.Click += new System.EventHandler(this.BTNSaveXML_Click);
			// 
			// FormP
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.BTNSaveXML);
			this.Controls.Add(this.BTNPrintare);
			this.Controls.Add(this.BTNSaveDB);
			this.Controls.Add(this.BTNCalculSalarii);
			this.Controls.Add(this.DGVProfesori);
			this.KeyPreview = true;
			this.Name = "FormP";
			this.Text = "FormP";
			this.Load += new System.EventHandler(this.FormP_Load);
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.FormP_KeyDown);
			((System.ComponentModel.ISupportInitialize)(this.DGVProfesori)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.DataGridView DGVProfesori;
		private System.Windows.Forms.DataGridViewTextBoxColumn Marca;
		private System.Windows.Forms.DataGridViewTextBoxColumn Nume;
		private System.Windows.Forms.DataGridViewTextBoxColumn Salariu;
		private System.Windows.Forms.Button BTNCalculSalarii;
		private System.Windows.Forms.Button BTNSaveDB;
		private System.Drawing.Printing.PrintDocument printDocument1;
		private System.Windows.Forms.PrintPreviewDialog printPreviewDialog1;
		private System.Windows.Forms.Button BTNPrintare;
		private System.Windows.Forms.Button BTNSaveXML;
	}
}

