namespace ParcAuto
{
	partial class Form1
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
			this.LVVehicule = new System.Windows.Forms.ListView();
			this.NrMatricol = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.Categorie = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.Kilometraj = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.NumarUsi = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.AreRoataDeRezerva = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.NrRemorci = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.CantitateRemorca = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.BTNDelete = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// LVVehicule
			// 
			this.LVVehicule.CheckBoxes = true;
			this.LVVehicule.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.NrMatricol,
            this.Categorie,
            this.Kilometraj,
            this.NumarUsi,
            this.AreRoataDeRezerva,
            this.NrRemorci,
            this.CantitateRemorca});
			this.LVVehicule.HideSelection = false;
			this.LVVehicule.Location = new System.Drawing.Point(12, 12);
			this.LVVehicule.Name = "LVVehicule";
			this.LVVehicule.Size = new System.Drawing.Size(776, 323);
			this.LVVehicule.TabIndex = 0;
			this.LVVehicule.UseCompatibleStateImageBehavior = false;
			this.LVVehicule.View = System.Windows.Forms.View.Details;
			// 
			// NrMatricol
			// 
			this.NrMatricol.Text = "Nr. Matricol";
			this.NrMatricol.Width = 77;
			// 
			// Categorie
			// 
			this.Categorie.Text = "Categorie";
			// 
			// Kilometraj
			// 
			this.Kilometraj.Text = "Kilometraj";
			// 
			// NumarUsi
			// 
			this.NumarUsi.Text = "Numar Usi";
			this.NumarUsi.Width = 68;
			// 
			// AreRoataDeRezerva
			// 
			this.AreRoataDeRezerva.Text = "Are Roata De Rezerva";
			this.AreRoataDeRezerva.Width = 116;
			// 
			// NrRemorci
			// 
			this.NrRemorci.Text = "Nr. Remorci";
			this.NrRemorci.Width = 71;
			// 
			// CantitateRemorca
			// 
			this.CantitateRemorca.Text = "Cantitate Remorca";
			this.CantitateRemorca.Width = 105;
			// 
			// BTNDelete
			// 
			this.BTNDelete.Location = new System.Drawing.Point(12, 341);
			this.BTNDelete.Name = "BTNDelete";
			this.BTNDelete.Size = new System.Drawing.Size(75, 23);
			this.BTNDelete.TabIndex = 1;
			this.BTNDelete.Text = "Delete";
			this.BTNDelete.UseVisualStyleBackColor = true;
			this.BTNDelete.Click += new System.EventHandler(this.BTNDelete_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.BTNDelete);
			this.Controls.Add(this.LVVehicule);
			this.Name = "Form1";
			this.Text = "Form1";
			this.Load += new System.EventHandler(this.Form1_Load);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ListView LVVehicule;
		private System.Windows.Forms.ColumnHeader NrMatricol;
		private System.Windows.Forms.ColumnHeader Categorie;
		private System.Windows.Forms.ColumnHeader Kilometraj;
		private System.Windows.Forms.ColumnHeader NumarUsi;
		private System.Windows.Forms.ColumnHeader AreRoataDeRezerva;
		private System.Windows.Forms.ColumnHeader NrRemorci;
		private System.Windows.Forms.ColumnHeader CantitateRemorca;
		private System.Windows.Forms.Button BTNDelete;
	}
}

