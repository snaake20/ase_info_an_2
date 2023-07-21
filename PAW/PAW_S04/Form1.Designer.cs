namespace PAW_S04
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
			this.tbCod = new System.Windows.Forms.TextBox();
			this.lCod = new System.Windows.Forms.Label();
			this.cbSex = new System.Windows.Forms.ComboBox();
			this.lSex = new System.Windows.Forms.Label();
			this.tbVarsta = new System.Windows.Forms.TextBox();
			this.lVarsta = new System.Windows.Forms.Label();
			this.tbNume = new System.Windows.Forms.TextBox();
			this.tbNote = new System.Windows.Forms.TextBox();
			this.lNume = new System.Windows.Forms.Label();
			this.lNote = new System.Windows.Forms.Label();
			this.btnCreare = new System.Windows.Forms.Button();
			this.btnVizualizareStudenti = new System.Windows.Forms.Button();
			this.form1ErrorProvider = new System.Windows.Forms.ErrorProvider(this.components);
			this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.schimbaCuloareFundalToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.schimbaFontToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			((System.ComponentModel.ISupportInitialize)(this.form1ErrorProvider)).BeginInit();
			this.contextMenuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// tbCod
			// 
			this.tbCod.Location = new System.Drawing.Point(93, 12);
			this.tbCod.Name = "tbCod";
			this.tbCod.Size = new System.Drawing.Size(100, 20);
			this.tbCod.TabIndex = 0;
			// 
			// lCod
			// 
			this.lCod.AutoSize = true;
			this.lCod.Location = new System.Drawing.Point(20, 16);
			this.lCod.Name = "lCod";
			this.lCod.Size = new System.Drawing.Size(69, 13);
			this.lCod.TabIndex = 1;
			this.lCod.Text = "Cod Student:";
			// 
			// cbSex
			// 
			this.cbSex.FormattingEnabled = true;
			this.cbSex.Items.AddRange(new object[] {
            "F",
            "M"});
			this.cbSex.Location = new System.Drawing.Point(93, 38);
			this.cbSex.Name = "cbSex";
			this.cbSex.Size = new System.Drawing.Size(100, 21);
			this.cbSex.TabIndex = 2;
			// 
			// lSex
			// 
			this.lSex.AutoSize = true;
			this.lSex.Location = new System.Drawing.Point(20, 41);
			this.lSex.Name = "lSex";
			this.lSex.Size = new System.Drawing.Size(28, 13);
			this.lSex.TabIndex = 3;
			this.lSex.Text = "Sex:";
			// 
			// tbVarsta
			// 
			this.tbVarsta.Location = new System.Drawing.Point(93, 65);
			this.tbVarsta.Name = "tbVarsta";
			this.tbVarsta.Size = new System.Drawing.Size(100, 20);
			this.tbVarsta.TabIndex = 4;
			// 
			// lVarsta
			// 
			this.lVarsta.AutoSize = true;
			this.lVarsta.Location = new System.Drawing.Point(20, 65);
			this.lVarsta.Name = "lVarsta";
			this.lVarsta.Size = new System.Drawing.Size(40, 13);
			this.lVarsta.TabIndex = 5;
			this.lVarsta.Text = "Varsta:";
			// 
			// tbNume
			// 
			this.tbNume.Location = new System.Drawing.Point(93, 92);
			this.tbNume.Name = "tbNume";
			this.tbNume.Size = new System.Drawing.Size(100, 20);
			this.tbNume.TabIndex = 6;
			// 
			// tbNote
			// 
			this.tbNote.Location = new System.Drawing.Point(93, 119);
			this.tbNote.Name = "tbNote";
			this.tbNote.Size = new System.Drawing.Size(100, 20);
			this.tbNote.TabIndex = 7;
			// 
			// lNume
			// 
			this.lNume.AutoSize = true;
			this.lNume.Location = new System.Drawing.Point(22, 95);
			this.lNume.Name = "lNume";
			this.lNume.Size = new System.Drawing.Size(38, 13);
			this.lNume.TabIndex = 8;
			this.lNume.Text = "Nume:";
			// 
			// lNote
			// 
			this.lNote.AutoSize = true;
			this.lNote.Location = new System.Drawing.Point(23, 125);
			this.lNote.Name = "lNote";
			this.lNote.Size = new System.Drawing.Size(33, 13);
			this.lNote.TabIndex = 9;
			this.lNote.Text = "Note:";
			// 
			// btnCreare
			// 
			this.btnCreare.Location = new System.Drawing.Point(23, 158);
			this.btnCreare.Name = "btnCreare";
			this.btnCreare.Size = new System.Drawing.Size(170, 23);
			this.btnCreare.TabIndex = 10;
			this.btnCreare.Text = "Creare Student";
			this.btnCreare.UseVisualStyleBackColor = true;
			this.btnCreare.Click += new System.EventHandler(this.btnCreare_Click);
			// 
			// btnVizualizareStudenti
			// 
			this.btnVizualizareStudenti.Location = new System.Drawing.Point(25, 187);
			this.btnVizualizareStudenti.Name = "btnVizualizareStudenti";
			this.btnVizualizareStudenti.Size = new System.Drawing.Size(168, 23);
			this.btnVizualizareStudenti.TabIndex = 11;
			this.btnVizualizareStudenti.Text = "&Vizualizare Studenti";
			this.btnVizualizareStudenti.UseVisualStyleBackColor = true;
			this.btnVizualizareStudenti.Click += new System.EventHandler(this.btnVizualizareStudenti_Click);
			// 
			// form1ErrorProvider
			// 
			this.form1ErrorProvider.ContainerControl = this;
			// 
			// contextMenuStrip1
			// 
			this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.schimbaCuloareFundalToolStripMenuItem,
            this.schimbaFontToolStripMenuItem});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new System.Drawing.Size(200, 48);
			// 
			// schimbaCuloareFundalToolStripMenuItem
			// 
			this.schimbaCuloareFundalToolStripMenuItem.Name = "schimbaCuloareFundalToolStripMenuItem";
			this.schimbaCuloareFundalToolStripMenuItem.Size = new System.Drawing.Size(199, 22);
			this.schimbaCuloareFundalToolStripMenuItem.Text = "Schimba culoare fundal";
			this.schimbaCuloareFundalToolStripMenuItem.Click += new System.EventHandler(this.schimbaCuloareFundalToolStripMenuItem_Click);
			// 
			// schimbaFontToolStripMenuItem
			// 
			this.schimbaFontToolStripMenuItem.Name = "schimbaFontToolStripMenuItem";
			this.schimbaFontToolStripMenuItem.Size = new System.Drawing.Size(199, 22);
			this.schimbaFontToolStripMenuItem.Text = "Schimba font";
			this.schimbaFontToolStripMenuItem.Click += new System.EventHandler(this.schimbaFontToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.ContextMenuStrip = this.contextMenuStrip1;
			this.Controls.Add(this.btnVizualizareStudenti);
			this.Controls.Add(this.btnCreare);
			this.Controls.Add(this.lNote);
			this.Controls.Add(this.lNume);
			this.Controls.Add(this.tbNote);
			this.Controls.Add(this.tbNume);
			this.Controls.Add(this.lVarsta);
			this.Controls.Add(this.tbVarsta);
			this.Controls.Add(this.lSex);
			this.Controls.Add(this.cbSex);
			this.Controls.Add(this.lCod);
			this.Controls.Add(this.tbCod);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.Name = "Form1";
			this.Text = "Form Student";
			((System.ComponentModel.ISupportInitialize)(this.form1ErrorProvider)).EndInit();
			this.contextMenuStrip1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox tbCod;
		private System.Windows.Forms.Label lCod;
		private System.Windows.Forms.ComboBox cbSex;
		private System.Windows.Forms.Label lSex;
		private System.Windows.Forms.TextBox tbVarsta;
		private System.Windows.Forms.Label lVarsta;
		private System.Windows.Forms.TextBox tbNume;
		private System.Windows.Forms.TextBox tbNote;
		private System.Windows.Forms.Label lNume;
		private System.Windows.Forms.Label lNote;
		private System.Windows.Forms.Button btnCreare;
		private System.Windows.Forms.Button btnVizualizareStudenti;
		private System.Windows.Forms.ErrorProvider form1ErrorProvider;
		private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
		private System.Windows.Forms.ToolStripMenuItem schimbaCuloareFundalToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem schimbaFontToolStripMenuItem;
	}
}

