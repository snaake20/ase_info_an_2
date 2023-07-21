namespace PAW_S08
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
			this.components = new System.ComponentModel.Container();
			this.tbCod = new System.Windows.Forms.TextBox();
			this.tbNota = new System.Windows.Forms.TextBox();
			this.tbNume = new System.Windows.Forms.TextBox();
			this.btnAdaugaStudent = new System.Windows.Forms.Button();
			this.listView1 = new System.Windows.Forms.ListView();
			this.Cod = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.Nume = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.Nota = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
			this.CMSListView = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.stergeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.btnAfisare = new System.Windows.Forms.Button();
			this.btnSterge = new System.Windows.Forms.Button();
			this.btnSalvare = new System.Windows.Forms.Button();
			this.CMSListView.SuspendLayout();
			this.SuspendLayout();
			// 
			// tbCod
			// 
			this.tbCod.Location = new System.Drawing.Point(13, 13);
			this.tbCod.Name = "tbCod";
			this.tbCod.Size = new System.Drawing.Size(100, 20);
			this.tbCod.TabIndex = 0;
			// 
			// tbNota
			// 
			this.tbNota.Location = new System.Drawing.Point(12, 65);
			this.tbNota.Name = "tbNota";
			this.tbNota.Size = new System.Drawing.Size(100, 20);
			this.tbNota.TabIndex = 2;
			// 
			// tbNume
			// 
			this.tbNume.Location = new System.Drawing.Point(12, 39);
			this.tbNume.Name = "tbNume";
			this.tbNume.Size = new System.Drawing.Size(100, 20);
			this.tbNume.TabIndex = 1;
			// 
			// btnAdaugaStudent
			// 
			this.btnAdaugaStudent.Location = new System.Drawing.Point(13, 91);
			this.btnAdaugaStudent.Name = "btnAdaugaStudent";
			this.btnAdaugaStudent.Size = new System.Drawing.Size(75, 23);
			this.btnAdaugaStudent.TabIndex = 3;
			this.btnAdaugaStudent.Text = "Adauga";
			this.btnAdaugaStudent.UseVisualStyleBackColor = true;
			this.btnAdaugaStudent.Click += new System.EventHandler(this.btnAdaugaStudent_Click);
			// 
			// listView1
			// 
			this.listView1.CheckBoxes = true;
			this.listView1.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.Cod,
            this.Nume,
            this.Nota});
			this.listView1.ContextMenuStrip = this.CMSListView;
			this.listView1.FullRowSelect = true;
			this.listView1.GridLines = true;
			this.listView1.HideSelection = false;
			this.listView1.Location = new System.Drawing.Point(134, 12);
			this.listView1.MultiSelect = false;
			this.listView1.Name = "listView1";
			this.listView1.Size = new System.Drawing.Size(595, 97);
			this.listView1.TabIndex = 5;
			this.listView1.UseCompatibleStateImageBehavior = false;
			this.listView1.View = System.Windows.Forms.View.Details;
			this.listView1.ItemChecked += new System.Windows.Forms.ItemCheckedEventHandler(this.listView1_ItemChecked);
			// 
			// Cod
			// 
			this.Cod.Text = "Cod";
			// 
			// Nume
			// 
			this.Nume.Text = "Nume";
			// 
			// Nota
			// 
			this.Nota.Text = "Nota";
			// 
			// CMSListView
			// 
			this.CMSListView.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.stergeToolStripMenuItem});
			this.CMSListView.Name = "CMSListView";
			this.CMSListView.Size = new System.Drawing.Size(108, 26);
			// 
			// stergeToolStripMenuItem
			// 
			this.stergeToolStripMenuItem.Name = "stergeToolStripMenuItem";
			this.stergeToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
			this.stergeToolStripMenuItem.Text = "Sterge";
			this.stergeToolStripMenuItem.Click += new System.EventHandler(this.stergeToolStripMenuItem_Click);
			// 
			// btnAfisare
			// 
			this.btnAfisare.Location = new System.Drawing.Point(134, 126);
			this.btnAfisare.Name = "btnAfisare";
			this.btnAfisare.Size = new System.Drawing.Size(75, 23);
			this.btnAfisare.TabIndex = 6;
			this.btnAfisare.Text = "Afisare";
			this.btnAfisare.UseVisualStyleBackColor = true;
			this.btnAfisare.Click += new System.EventHandler(this.btnAfisare_Click);
			// 
			// btnSterge
			// 
			this.btnSterge.Location = new System.Drawing.Point(215, 126);
			this.btnSterge.Name = "btnSterge";
			this.btnSterge.Size = new System.Drawing.Size(75, 23);
			this.btnSterge.TabIndex = 7;
			this.btnSterge.Text = "Sterge";
			this.btnSterge.UseVisualStyleBackColor = true;
			this.btnSterge.Click += new System.EventHandler(this.btnSterge_Click);
			// 
			// btnSalvare
			// 
			this.btnSalvare.Location = new System.Drawing.Point(296, 126);
			this.btnSalvare.Name = "btnSalvare";
			this.btnSalvare.Size = new System.Drawing.Size(75, 23);
			this.btnSalvare.TabIndex = 8;
			this.btnSalvare.Text = "Salvare";
			this.btnSalvare.UseVisualStyleBackColor = true;
			this.btnSalvare.Click += new System.EventHandler(this.btnSalvare_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.btnSalvare);
			this.Controls.Add(this.btnSterge);
			this.Controls.Add(this.btnAfisare);
			this.Controls.Add(this.listView1);
			this.Controls.Add(this.btnAdaugaStudent);
			this.Controls.Add(this.tbNume);
			this.Controls.Add(this.tbNota);
			this.Controls.Add(this.tbCod);
			this.Name = "Form1";
			this.Text = "Form1";
			this.CMSListView.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox tbCod;
		private System.Windows.Forms.TextBox tbNota;
		private System.Windows.Forms.TextBox tbNume;
		private System.Windows.Forms.Button btnAdaugaStudent;
		private System.Windows.Forms.ListView listView1;
		private System.Windows.Forms.ColumnHeader Cod;
		private System.Windows.Forms.ColumnHeader Nume;
		private System.Windows.Forms.ColumnHeader Nota;
		private System.Windows.Forms.Button btnAfisare;
		private System.Windows.Forms.Button btnSterge;
		private System.Windows.Forms.ContextMenuStrip CMSListView;
		private System.Windows.Forms.ToolStripMenuItem stergeToolStripMenuItem;
		private System.Windows.Forms.Button btnSalvare;
	}
}

