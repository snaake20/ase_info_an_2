namespace PregatireTest1
{
	partial class MeniuPrincipal
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
			this.LbMateriale = new System.Windows.Forms.ListBox();
			this.BtnAdaugareMaterial = new System.Windows.Forms.Button();
			this.CMSLbMateriale = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.editeazaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.stergeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.CMSLbMateriale.SuspendLayout();
			this.SuspendLayout();
			// 
			// LbMateriale
			// 
			this.LbMateriale.ContextMenuStrip = this.CMSLbMateriale;
			this.LbMateriale.FormattingEnabled = true;
			this.LbMateriale.Location = new System.Drawing.Point(95, 12);
			this.LbMateriale.Name = "LbMateriale";
			this.LbMateriale.Size = new System.Drawing.Size(672, 199);
			this.LbMateriale.TabIndex = 0;
			// 
			// BtnAdaugareMaterial
			// 
			this.BtnAdaugareMaterial.Location = new System.Drawing.Point(12, 12);
			this.BtnAdaugareMaterial.Name = "BtnAdaugareMaterial";
			this.BtnAdaugareMaterial.Size = new System.Drawing.Size(75, 23);
			this.BtnAdaugareMaterial.TabIndex = 1;
			this.BtnAdaugareMaterial.Text = "Adauga Materiale";
			this.BtnAdaugareMaterial.UseVisualStyleBackColor = true;
			this.BtnAdaugareMaterial.Click += new System.EventHandler(this.BtnAdaugareMaterial_Click);
			// 
			// CMSLbMateriale
			// 
			this.CMSLbMateriale.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.editeazaToolStripMenuItem,
            this.stergeToolStripMenuItem});
			this.CMSLbMateriale.Name = "CMSLbMateriale";
			this.CMSLbMateriale.Size = new System.Drawing.Size(181, 70);
			// 
			// editeazaToolStripMenuItem
			// 
			this.editeazaToolStripMenuItem.Name = "editeazaToolStripMenuItem";
			this.editeazaToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.editeazaToolStripMenuItem.Text = "Editeaza";
			this.editeazaToolStripMenuItem.Click += new System.EventHandler(this.editeazaToolStripMenuItem_Click);
			// 
			// stergeToolStripMenuItem
			// 
			this.stergeToolStripMenuItem.Name = "stergeToolStripMenuItem";
			this.stergeToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.stergeToolStripMenuItem.Text = "Sterge";
			this.stergeToolStripMenuItem.Click += new System.EventHandler(this.stergeToolStripMenuItem_Click);
			// 
			// MeniuPrincipal
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.BtnAdaugareMaterial);
			this.Controls.Add(this.LbMateriale);
			this.Name = "MeniuPrincipal";
			this.Text = "Form1";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.MeniuPrincipal_FormClosed);
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.MeniuPrincipal_KeyDown);
			this.CMSLbMateriale.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ListBox LbMateriale;
		private System.Windows.Forms.Button BtnAdaugareMaterial;
		private System.Windows.Forms.ContextMenuStrip CMSLbMateriale;
		private System.Windows.Forms.ToolStripMenuItem editeazaToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem stergeToolStripMenuItem;
	}
}

